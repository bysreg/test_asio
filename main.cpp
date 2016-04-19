#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using namespace std;

void lambda_example()
{
	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	std::for_each(
		in(std::cin), in(), std::cout << (boost::lambda::_1 * 3) << " " );
}

void timer_blocking_example()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.wait();

	cout<<"hello world"<<endl;
}

void callback(const boost::system::error_code&)
{
	cout<<"hello world"<<endl;
}

void timer_nonblocking_example()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(&callback);

	io.run(); // need this call for non blocking
}

void callback_1(const boost::system::error_code&, 
	boost::asio::deadline_timer* t, int* count)
{
	if(*count < 5)
	{
		cout<<*count<<endl;
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(callback_1, boost::asio::placeholders::error, t, count));
	}
}

void timer_nonblocking_multiple_argument_callback_example()
{
	boost::asio::io_service io;
	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(callback_1, boost::asio::placeholders::error, &t, &count));

	io.run();
}

class Callback
{
	public:
	boost::asio::io_service io;
	boost::asio::deadline_timer timer_;
	int count_;

	void callback()
	{
		if(count_ < 5)
		{
			cout << count_ << endl;
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&Callback::callback, this));
		}
	}

	Callback(boost::asio::io_service& io) : 
		timer_(io, boost::posix_time::seconds(1)), 
		count_(0)
	{
		timer_.async_wait(boost::bind(&Callback::callback, this));
	}
};

void timer_nonblocking_class_example()
{
	boost::asio::io_service io;
	Callback c(io);
	
	io.run();
}

int main()
{
	//lambda_example();
	//timer_blocking_example();
	//timer_nonblocking_example();
	//timer_nonblocking_multiple_argument_callback_example();
	timer_nonblocking_class_example();
	return 0;
}

