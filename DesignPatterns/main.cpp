#include <iostream>

#include "Builder/BlogPostBuilder.hpp"
#include "Factory/LinuxWidgetsFactory.hpp"
#include "Factory/WindowsWidgetsFactory.hpp"

int main()
{
#ifdef _WIN32
    auto wwf = std::make_unique<WindowsWidgetsFactory>();
    wwf->createButton()->paint();
    wwf->createCheckBox()->paint();
    wwf->createField()->paint();
#elif __linux__
    auto lwf = std::make_unique<LinuxWidgetsFactory>();
    lwf->createButton()->paint();
    lwf->createCheckBox()->paint();
    lwf->createField()->paint();
#endif

    auto pbp      = std::make_unique<BlogPostBuilder>();
    auto blogPost = pbp->setTitle("title")->setBody("body")->getBlogPost();
    std::cout << blogPost->body << " " << blogPost->title << std::endl;

    return 0;
}