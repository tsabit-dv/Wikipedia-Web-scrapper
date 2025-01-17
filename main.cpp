#include <iostream>
#include <string>
#include <curl/curl.h>
#include <gumbo.h>

namespace WikipediaScraper {

    size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        if (!userp) return 0;
        userp->append(static_cast<char*>(contents), size * nmemb);
        return size * nmemb;
    }

    class HttpClient {
    public:
        static std::string fetchHTML(const std::string& url) {
            CURL* curl = curl_easy_init();
            if (!curl) {
                throw std::runtime_error("Failed to initialize CURL");
            }

            std::string response;
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::string error = "CURL error: " + std::string(curl_easy_strerror(res));
                curl_easy_cleanup(curl);
                throw std::runtime_error(error);
            }

            curl_easy_cleanup(curl);
            return response;
        }
    };

    void searchForText(GumboNode* node, const std::string& tag, std::string& result) {
        if (!node || node->type != GUMBO_NODE_ELEMENT) return;

        if (node->v.element.tag == GUMBO_TAG_H1) {
            GumboAttribute* idAttr = gumbo_get_attribute(&node->v.element.attributes, "id");
            if (idAttr && idAttr->value == tag) {
                GumboNode* textNode = static_cast<GumboNode*>(node->v.element.children.data[0]);
                if (textNode && textNode->type == GUMBO_NODE_TEXT) {
                    result = textNode->v.text.text;
                    return;
                }
            }
        }

        const GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            searchForText(static_cast<GumboNode*>(children->data[i]), tag, result);
        }
    }

    std::string extractTitle(const std::string& html) {
        GumboOutput* output = gumbo_parse(html.c_str());
        if (!output) {
            throw std::runtime_error("Failed to parse HTML using Gumbo");
        }

        std::string heading;
        searchForText(output->root, "firstHeading", heading);
        gumbo_destroy_output(&kGumboDefaultOptions, output);

        if (heading.empty()) {
            throw std::runtime_error("Failed to extract title from HTML");
        }

        return heading;
    }

}

int main() {
    try {
        // URL target (Wikipedia)
        const std::string url = "https://en.wikipedia.org/wiki/Web_scraping";

        std::cout << "Fetching HTML from: " << url << std::endl;
        std::string html = WikipediaScraper::HttpClient::fetchHTML(url);
      
        std::cout << "Parsing HTML to extract title..." << std::endl;
        std::string title = WikipediaScraper::extractTitle(html);

        std::cout << "Page Title: " << title << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
