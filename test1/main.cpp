
#include <iostream>

#include <chrono>

#include "asio.hpp"

#include "asio/system_timer.hpp"

// io_service: http://think-async.com/Asio/asio-1.10.6/doc/asio/reference/io_service.html
// timers: http://think-async.com/Asio/asio-1.10.6/doc/asio/overview/timers.html

int main()
{
	asio::io_service i;
	// asio::deadline_timer t(i);
	// asio::basic_waitable_timer::system_timer t(i);
	asio::system_timer t(i);

	t.expires_from_now(std::chrono::milliseconds(5000));
	// t.expires_from_now(std::chrono::seconds(5));

	t.wait();

	//std::chrono::time_point<std::chrono::system_clock> start, end;

	//end = std::chrono::system_clock::now();

	asio::error_code ec;

	i.run(ec);

	std::cout << "error code: " << ec.value() << std::endl;

	return 0;
}
