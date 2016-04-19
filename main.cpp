#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void lambda_example() 
{
	using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
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



int main()
{
	//lambda_example();
	//timer_blocking_example();	
	timer_nonblocking_example();
	return 0;
}

