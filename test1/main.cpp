
#include <iostream>

#include <chrono>

#include "asio.hpp"

#include "asio/system_timer.hpp"

// io_service: http://think-async.com/Asio/asio-1.10.6/doc/asio/reference/io_service.html
// timers: http://think-async.com/Asio/asio-1.10.6/doc/asio/overview/timers.html

int main()
{
	asio::io_service i;
	asio::system_timer t(i);

	t.expires_from_now(std::chrono::milliseconds(5000));

	t.wait();

	asio::error_code ec;

	i.run(ec);

	std::cout << "error code: " << ec.value() << std::endl;

	return 0;
}
