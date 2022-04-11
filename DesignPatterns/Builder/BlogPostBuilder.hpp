#pragma once
#include "BlogPostBuilderCRTP.hpp"

class BlogPostBuilder : public BlogPostBuilderCRTP<BlogPostBuilder>
{
public:
    BlogPostBuilder* setTitle(std::string title)
    {
        this->_spBlogPost->title = std::move(title);
        return this;
    }

    BlogPostBuilder* setBody(std::string body)
    {
        this->_spBlogPost->body = std::move(body);
        return this;
    }

    BlogPostBuilder* setTags(std::vector<std::string> tags)
    {
        this->_spBlogPost->tags = std::move(tags);
        return this;
    }

    BlogPostBuilder* setCategories(std::vector<std::string> categories)
    {
        this->_spBlogPost->categories = std::move(categories);
        return this;
    }

    std::shared_ptr<BlogPost> getBlogPost() const
    {
        return this->_spBlogPost;
    }
};
