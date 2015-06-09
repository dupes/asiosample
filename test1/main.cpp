
#include <iostream>

#include <functional>
#include <chrono>

#include "asio.hpp"

#include "asio/system_timer.hpp"
#include "asio/steady_timer.hpp"

//#include "asio/detail/bind_handler.hpp"
#include "asio/placeholders.hpp"

#include <memory>
#include <thread>



// io_service: http://think-async.com/Asio/asio-1.10.6/doc/asio/reference/io_service.html
// timers: http://think-async.com/Asio/asio-1.10.6/doc/asio/overview/timers.html
// http://en.cppreference.com/w/cpp/chrono
// http://blog.think-async.com/2010/04/bind-illustrated.html
// http://stackoverflow.com/questions/9048119/why-cant-stdbind-and-boostbind-be-used-interchangeably-in-this-boost-asio-t
// * use lamdas

// http://curl.haxx.se/libcurl/c/asiohiper.html
// * curl with ASIO

void handler(int *x, const asio::error_code &ec)
{
	std::cout << "handler called" << std::endl;
}

void handler2(const asio::error_code &ec)
{
	std::cout << "handler 2 called" << std::endl;
}

int main()
{
	asio::io_service i;
	// asio::io_service::work work(i);

	asio::system_timer t(i);

	//t.expires_from_now(std::chrono::milliseconds(5000));

	t.expires_at(std::chrono::system_clock::now() + std::chrono::milliseconds(3000));

	int x;

	// t.async_wait(handler2);
	t.async_wait(std::bind(handler, &x, std::placeholders::_1));

	bool flag = false;

	i.run();


	return 0;
}
