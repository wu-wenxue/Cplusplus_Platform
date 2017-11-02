#include "http_client.h"
#include <curl/curl.h>
#include <string>
#include <iostream>

HttpClient::HttpClient():m_bDebug(false)
{

}

HttpClient::~HttpClient()
{

}

static int OnDebug(CURL*, curl_infotype itype,char* pData,size_t size, void*)
{
    Wxlogger* logger = Wxlogger::getInstance();
    if(itype == CURLINFO_TEXT)
    {
        WXLOG_WARN(logger,"[TEXT] : " << pData);
    }
    else if (itype == CURLINFO_HEADER_IN)
    {
        WXLOG_WARN(logger,"[HEADER_IN] : " << pData);
    }
    else if(itype == CURLINFO_HEADER_OUT)
    {
        WXLOG_WARN(logger,"[HEADER_OUT] : " << pData);
    }
    else if(itype == CURLINFO_DATA_IN)
    {
        WXLOG_WARN(logger,"[DATA_IN] : " << pData);
    }
    else if(itype == CURLINFO_DATA_OUT)
    {
        WXLOG_WARN(logger,"[DATA_OUT] : " << pData);
    }

    return 0;
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if(NULL == str || NULL == buffer)
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData,size * nmemb);
    return nmemb;
}



int HttpClient::Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;

}

int HttpClient::Get(const std::string & strUrl, std::string & strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
    }
//    <pre name="code" class="cpp">
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    /**
        * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
        * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
        */
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;

}

int HttpClient::Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        //缺省情况就是PEM，所以无需设置，另外支持DER
        //curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;

}

int HttpClient::Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;

}

static size_t httpDownloadHandler(void* data,size_t size,size_t nmemb, void* stream)
{
    std::cout << "httpDownloadHandler" <<std::endl;
    FILE* file = (FILE*)stream;

    if(file)
    {
        return fwrite(data,size,nmemb,file);
    }
    return -1;
}

int HttpClient::Download(const std::string& strUrl,const char* file)
{
    FILE* fp;
    short ec = 0;
    long code = 0;
    CURL* curl;
    CURLcode status;

    if(strUrl.empty() || NULL == file)
    {
        return -1;
    }

    fp = fopen(file,"w");
    if(NULL == fp)
    {
        return -1;
    }

    curl = curl_easy_init();
    if( NULL == curl)
    {
        fclose(fp);
        return -1;
    }

    curl_easy_setopt(curl,CURLOPT_URL,strUrl.c_str());
    curl_easy_setopt(curl,CURLOPT_TIMEOUT,60);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,httpDownloadHandler);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0L);
    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0L);

    status = curl_easy_perform(curl);
    curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&code);
    if(!(200 == code && CURLE_OK == status))
    {
        return -1;
    }

    curl_easy_cleanup(curl);
    fflush(fp);
    fclose(fp);

    return 0;
}

void HttpClient::SetDebug(bool bDebug)
{
    m_bDebug = bDebug;
}
