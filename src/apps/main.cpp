/**
 * @file app/main.cpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/timer.hpp>

#include <common/RootCoordinator.hpp>
#include <common/scheduler/VectorScheduler.hpp>
#include <common/scheduler/HeapScheduler.hpp>

#include <kernel/pdevs/Coordinator.hpp>

#include <tests/mixed/models.hpp>
#include <tests/mixed/graph_manager.hpp>

using namespace paradevs::tests::mixed;

template < int size >
void run_flat_with_heap()
{
    boost::timer t;

    std::cout << "run_flat_with_heap [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                paradevs::common::DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            LinearGraphManager < size, SchedulerHandle > >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

template < int size >
void run_flat_with_vector()
{
    boost::timer t;

    std::cout << "run_flat_with_vector [" << size << "] ..." << std::endl;

    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            LinearGraphManager <
                size, paradevs::common::scheduler::NoSchedulerHandle > >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();

    std::cout << "... OK -> " << t.elapsed() << std::endl;
}

void run_hierarchic_with_heap()
{
    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::HeapScheduler <
                paradevs::common::DoubleTime, SchedulerHandle >,
            SchedulerHandle,
            Root2GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();
}

void run_hierarchic_with_vector()
{
    paradevs::common::RootCoordinator <
        paradevs::common::DoubleTime, paradevs::pdevs::Coordinator <
            paradevs::common::DoubleTime,
            paradevs::common::scheduler::VectorScheduler <
                paradevs::common::DoubleTime >,
            paradevs::common::scheduler::NoSchedulerHandle,
            Root3GraphManager >
        > rc(0, 100, "root", paradevs::common::NoParameters(),
             paradevs::common::NoParameters());

    paradevs::common::Trace < paradevs::common::DoubleTime >::trace().clear();
    rc.run();
}

// int main()
// {
//     boost::timer t;

//     srand(108364);

//     run_flat_with_heap < 10 >();
//     run_flat_with_heap < 20 >();
//     run_flat_with_heap < 30 >();
//     run_flat_with_heap < 40 >();
//     run_flat_with_heap < 50 >();
//     run_flat_with_heap < 60 >();
//     run_flat_with_heap < 70 >();
//     run_flat_with_heap < 80 >();
//     run_flat_with_heap < 90 >();
//     run_flat_with_heap < 100 >();
//     run_flat_with_heap < 200 >();

//     run_flat_with_vector < 10 >();
//     run_flat_with_vector < 20 >();
//     run_flat_with_vector < 30 >();
//     run_flat_with_vector < 40 >();
//     run_flat_with_vector < 50 >();
//     run_flat_with_vector < 60 >();
//     run_flat_with_vector < 70 >();
//     run_flat_with_vector < 80 >();
//     run_flat_with_vector < 90 >();
//     run_flat_with_vector < 100 >();
//     run_flat_with_vector < 200 >();

//     double t2 = t.elapsed();

//     std::cout << "run_hierarchic_with_heap ..." << std::endl;
//     run_hierarchic_with_heap();

//     double t3 = t.elapsed();

//     std::cout << "... OK -> " << (t3 - t2) << std::endl;
//     std::cout << "run_hierarchic_with_vector ..." << std::endl;
//     run_hierarchic_with_vector();

//     double t4 = t.elapsed();

//     std::cout << "... OK -> "  << (t4 - t3) << std::endl;
//     return 0;
// }

#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>

namespace messaging {

    struct message_base
    {
        virtual ~message_base()
        {}
    };

    template < typename Msg >
    struct wrapped_message : message_base
    {
        Msg contents;

        explicit wrapped_message(Msg const& contents_) : contents(contents_)
        { }
    };

    class queue
    {
    public:
        template < typename T >
        void push(T const& msg)
        {
            std::lock_guard < std::mutex > lk(m);

            q.push(std::make_shared < wrapped_message < T > >(msg));
            c.notify_all();
        }

        std::shared_ptr < message_base > wait_and_pop()
        {
            std::unique_lock < std::mutex > lk(m);

            c.wait(lk, [&]{ return !q.empty(); });
            auto res = q.front();
            q.pop();
            return res;
        }

    private:
        std::mutex m;
        std::condition_variable c;
        std::queue < std::shared_ptr < message_base > > q;
    };

    class close_queue
    { };

    class sender
    {
    public:
        sender() : q(nullptr)
        { }

        explicit sender(queue* q_) : q(q_)
        { }

        template < typename Message >
        void send(Message const& msg)
        {
            if (q) {
                q->push(msg);
            }
        }

    private:
        queue* q;
    };

    template < typename PreviousDispatcher, typename Msg, typename Func >
    class TemplateDispatcher
    {
    public:
        TemplateDispatcher(TemplateDispatcher&& other) : q(other.q),
                                                         prev(other.prev),
                                                         f(std::move(other.f)),
                                                         chained(other.chained)
        {
            other.chained = true;
        }

        TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
            q(q_), prev(prev_), f(std::forward < Func >(f_)), chained(false)
        {
            prev_->chained = true;
        }

        template < typename OtherMsg,
                   typename OtherFunc >
        TemplateDispatcher < TemplateDispatcher, OtherMsg, OtherFunc >
        handle(OtherFunc&& of)
        {
            return TemplateDispatcher<
                TemplateDispatcher, OtherMsg, OtherFunc>(
                    q, this, std::forward < OtherFunc >(of));
        }

        ~TemplateDispatcher() noexcept(false)
        {
            if (!chained) {
                wait_and_dispatch();
            }
        }

    private:
        TemplateDispatcher(TemplateDispatcher const&)=delete;

        TemplateDispatcher& operator=(TemplateDispatcher const&)=delete;

        template <typename Dispatcher, typename OtherMsg, typename OtherFunc >
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for(;;) {
                auto msg = q->wait_and_pop();

                if (dispatch(msg)) {
                    break;
                }
            }
        }

        bool dispatch(std::shared_ptr < message_base > const& msg)
        {
            if (wrapped_message < Msg >* wrapper =
                dynamic_cast < wrapped_message < Msg >* >(msg.get())) {
                f(wrapper->contents);
                return true;
            } else {
                return prev->dispatch(msg);
            }
        }

        queue* q;
        PreviousDispatcher* prev;
        Func f;
        bool chained;
    };

    class dispatcher
    {
    public:
        dispatcher(dispatcher&& other) : q(other.q), chained(other.chained)
        {
            other.chained = true;
        }

        explicit dispatcher(queue* q_) : q(q_), chained(false)
        {}

        template < typename Message, typename Func >
        TemplateDispatcher < dispatcher, Message, Func >
        handle(Func&& f)
        {
            return TemplateDispatcher < dispatcher, Message, Func >(
                q, this, std::forward < Func >(f));
        }

        ~dispatcher() noexcept(false)
        {
            if (!chained) {
                wait_and_dispatch();
            }
        }

    private:
        dispatcher(dispatcher const&)=delete;

        dispatcher& operator=(dispatcher const&)=delete;

        template<
            typename Dispatcher,
            typename Msg,
            typename Func>
        friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for(;;) {
                auto msg = q->wait_and_pop();

                dispatch(msg);
            }
        }

        bool dispatch(std::shared_ptr < message_base > const& msg)
        {
            if (dynamic_cast < wrapped_message < close_queue >* >(msg.get())) {
                throw close_queue();
            }
            return false;
        }

        queue* q;
        bool chained;
    };

    class receiver
    {
    public:
        operator sender()
        {
            return sender(&q);
        }

        dispatcher wait()
        {
            return dispatcher(&q);
        }

    private:
        queue q;
    };

} // namespace messaging

struct start
{ };

struct my_message
{ };

class A
{
public:
    A(messaging::sender b_) : b(b_)
    { }

    void done()
    { get_sender().send(messaging::close_queue()); }

    messaging::sender get_sender()
    { return incoming; }

    void run()
    {
        try
        {
            for(;;) {
                incoming.wait().handle < start >(
                    [&](start const& /* msg */)
                    {
                        std::cout << "start" << std::endl;
                        b.send(my_message());
                    }
                    );;
            }
        }
        catch(messaging::close_queue const&)
        { }
    }

private:
    messaging::receiver incoming;
    messaging::sender b;
};

class B
{
public:
    B()
    { }

    void done()
    { get_sender().send(messaging::close_queue()); }

    messaging::sender get_sender()
    { return incoming; }

    void run()
    {
        try
        {
            for(;;) {
                incoming.wait().handle < my_message >(
                    [&](my_message const& /* msg */)
                    { std::cout << "receive my message" << std::endl; }
                    );
            }
        }
        catch(messaging::close_queue const&)
        { }
    }

private:
    messaging::receiver incoming;
};

int main()
{
    B b;
    A a(b.get_sender());

    std::thread A_thread(&A::run, &a);
    std::thread B_thread(&B::run, &b);

    a.get_sender().send(start());
    sleep(1);

    a.done();
    b.done();
    A_thread.join();
    B_thread.join();
    return 0;
}
