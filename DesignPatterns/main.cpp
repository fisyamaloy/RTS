#include <iostream>

#include "Builder/BlogPostBuilder.hpp"
#include "Factory/LinuxWidgetsFactory.hpp"
#include "Factory/WindowsWidgetsFactory.hpp"
#include "Adapter/Adapter.hpp"

int main()
{
    std::unique_ptr<WidgetsFactoryAbstract> widgetsFactory;
#ifdef _WIN32
    widgetsFactory = std::make_unique<WindowsWidgetsFactory>();
#elif __linux__
    widgetsFactory = std::make_unique<LinuxWidgetsFactory>();
#endif
    widgetsFactory->createButton()->paint();
    widgetsFactory->createCheckBox()->paint();
    widgetsFactory->createField()->paint();

    
    auto pbp      = std::make_unique<BlogPostBuilder>();
    auto blogPost = pbp->setTitle("title")->setBody("body")->getBlogPost();
    std::cout << blogPost->body << " " << blogPost->title << std::endl;


    std::unique_ptr<BritishScales> bs = std::make_unique<BritishScales>(50);
    IScales* rScales = new RussianScales(55);
    IScales* bScales = new AdapterForBritishScales(std::move(bs));
    std::cout << rScales->getWeight() << std::endl;
    std::cout << bScales->getWeight() << std::endl;


    
    

    return 0;
}