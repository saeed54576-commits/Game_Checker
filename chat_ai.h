#ifndef CHAT_AI_H
#define CHAT_AI_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ChatAI {
public:
    // Set your OpenAI API key here
    static void setAPIKey(const std::string &key) {
        apiKey = key;
    }

    static std::string chat(const std::string &message) {
        CURL *curl = curl_easy_init();
        if (!curl) return "Error: Could not initialize CURL";

        std::string response;
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());

        json payload = {
            {"model", "gpt-3.5-turbo"},
            {"messages", json::array({
                {{"role", "user"}, {"content", message}}
            })},
            {"max_tokens", 500}
        };

        std::string payload_str = payload.dump();

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            return std::string("Error: ") + curl_easy_strerror(res);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        try {
            json response_json = json::parse(response);
            if (response_json.contains("choices") && response_json["choices"].size() > 0) {
                return response_json["choices"][0]["message"]["content"];
            }
            return "Error: Invalid response from API";
        } catch (...) {
            return "Error: Could not parse AI response";
        }
    }

private:
    static std::string apiKey;

    static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
        s->append((char *)contents, size * nmemb);
        return size * nmemb;
    }
};

std::string ChatAI::apiKey = "";

#endif // CHAT_AI_H
