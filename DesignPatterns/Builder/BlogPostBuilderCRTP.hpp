#pragma once
#include <memory>

#include "BlogPost.hpp"

template <class builder>
class BlogPostBuilderCRTP
{
    builder* self()
    {
        return static_cast<builder*>(this);
    }

    const builder* self() const
    {
        return static_cast<const builder*>(this);
    }

protected:
    std::shared_ptr<BlogPost> _spBlogPost;

public:
    BlogPostBuilderCRTP() : _spBlogPost(std::make_shared<BlogPost>()) {}

    builder* setTitle(std::string title)
    {
        return self()->setTitle(std::move(title));
    }
    builder* setBody(std::string body)
    {
        return self()->setBody(std::move(body));
    }
    builder* setTags(std::vector<std::string> tags)
    {
        return self()->setTags(std::move(tags));
    }
    builder* setCategories(std::vector<std::string> categories)
    {
        return self()->setCategories(std::move(categories));
    }

    std::shared_ptr<BlogPost> getBlogPost() const
    {
        return self()->getBlogPost();
    }
};
