#include <iostream>

#include "Factory/WindowsWidgetsFactory.hpp"
#include "Builder/BlogPostBuilder.hpp"

int main()
{
    auto wwf = std::make_unique<WindowsWidgetsFactory>();
    wwf->createButton()->paint();
    wwf->createCheckBox()->paint();
    wwf->createField()->paint();
    
    auto pbp = std::make_unique<BlogPostBuilder>();
    auto blogPost = pbp->setTitle("title")->setBody("body")->getBlogPost();
    std::cout << blogPost->body << " " << blogPost->title << std::endl;

    return 0;
}
