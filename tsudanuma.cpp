#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

void moji_find(std::vector<char>& test_find, std::vector<char>& real_find, std::vector<char>& result_str, std::vector<char>& marubatu_str)
{
    int cnt_pushback_first = 0;
    int cnt_pushback_second = 0;

    for (auto it_t = test_find.begin(); it_t != test_find.end(); ++it_t)
    {
        cnt_pushback_first = 0;
        int flag_find = 0;
        int cnt_find_X = 0;
        for (auto it_r = real_find.begin(); it_r != real_find.end(); ++it_r)
        {
            if(!flag_find)
            {
                if(cnt_pushback_first >= cnt_pushback_second)
                {
                    auto index_real = std::distance(real_find.begin(), it_r);
                    auto index_test = std::distance(test_find.begin(), it_t);
                    int index_int_real = (unsigned char) index_real;
                    int index_int_test = (unsigned char) index_test;
                    
                    if(*it_t == *it_r)
                    {
                        result_str.push_back(*it_t);
                        marubatu_str.push_back('O');
                        cnt_pushback_second = index_int_real + 1;
                        flag_find = 1;
                    }
                    else
                    {
                        result_str.push_back(' ');
                        cnt_find_X++;
                        marubatu_str.push_back('X');
                        if(real_find.size() == cnt_find_X)
                        {
                            for(int i(0); i < real_find.size(); i++)
                            {
                                result_str.pop_back();
                                marubatu_str.pop_back();
                            }
                        }
                    }
                }
            }
            cnt_pushback_first++;
        }
    }

    if (test_find.size() != real_find.size())
    {
        for (int i(0); i < real_find.size() + 1; i++)
        {
            if(test_find.size() < i && marubatu_str.size() < i)marubatu_str.push_back('X');
        }
    }

    if(marubatu_str.size() > real_find.size())
    {
        for(int i(0); i != real_find.size(); )
        {
            marubatu_str.pop_back();
            i = marubatu_str.size();
        }
    }
    
}

void moji_find_result(std::vector<char>& result_find, std::vector<char>& real_find, std::vector<char>& marubatu_str)
{
    std::cout << "Result/////////////////////////////////////////////////////////////////////////////////" << std::endl;
    for (auto it = result_find.begin(); it != result_find.end(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    for (auto it = real_find.begin(); it != real_find.end(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    for (auto it = marubatu_str.begin(); it != marubatu_str.end(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl << "End////////////////////////////////////////////////////////////////////////////////////" << std::endl;
}

void tudanuma_filter(std::vector<char>& marubatu_str, cv::Mat& maru_img, cv::Mat& batu_img)
{
    int cnt_maru = 0;

    for (auto it = marubatu_str.begin(); it != marubatu_str.end(); ++it)
    {
        if('O' == *it)cnt_maru++;
    }

    if(cnt_maru == 9)
    {
        cv::imshow("win", maru_img);
    }
    else cv::imshow("win2", batu_img);
}

void moji_kokuban(std::vector<char>& result_str, std::vector<char>& real_str, std::vector<char>& marubatu_str, std::string cv_cin, cv::Mat& clone_image)
{

    std::string result_cv, real_cv, marubatu_cv, compare_cv_match, compare_cv_discord;
    std::string result_str_str(result_str.begin(), result_str.end());
    std::string real_str_str(real_str.begin(), real_str.end());
    std::string marubatu_str_str(marubatu_str.begin(), marubatu_str.end()); 

    result_cv = "CONVERT_Result:     " + result_str_str; 
    real_cv = "TARGET_Word:        " + real_str_str; 
    marubatu_cv = "CIRCLE_and_CROSS:  " + marubatu_str_str;
    compare_cv_match = "COMPARE_Status:   Match";
    compare_cv_discord = "COMPARE_Status:   Discord";

    cv::putText(clone_image, cv_cin, cv::Point(25,75), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(0,0,0), 3);
    cv::putText(clone_image, result_cv, cv::Point(25,225), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(0,0,0), 3);
    cv::putText(clone_image, real_cv, cv::Point(25,375), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(0,0,0), 3);
    cv::putText(clone_image, marubatu_cv, cv::Point(25,525), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(0,0,0), 3);

    int cnt_maru = 0;

    for (auto it = marubatu_str.begin(); it != marubatu_str.end(); ++it)
    {
        if('O' == *it)cnt_maru++;
    }

    if(cnt_maru == 9)
    {
        cv::putText(clone_image, compare_cv_match, cv::Point(25,675), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(0,0,255), 3);
    }
    else cv::putText(clone_image, compare_cv_discord, cv::Point(25,675), cv::FONT_HERSHEY_SIMPLEX, 2.5, cv::Scalar(255,0,0), 3);
    
    cv::imshow("boad", clone_image);

    cv::waitKey(3000);

}

int main(){

    std::string str;
    std::string str_cin, str_cin_cv;
    std::vector<char> str_test;
    std::vector<char> str_result;
    std::vector<char> str_marubatu;
    std::vector<char> str_real = {'t','s','u','d','a','n','u','m','a'};

    cv::Mat img_maru, img_batu, img_boad, img_boad_clone;
    img_maru = cv::imread("/home/ikebe/Pictures/学校用/tudanuma_yes.jpg");
    img_batu = cv::imread("/home/ikebe/Pictures/学校用/tudanuma_filter.jpg");
    img_boad = cv::imread("/home/ikebe/Pictures/学校用/kokuban.jpg");
    resize(img_maru, img_maru, cv::Size(), 2, 2);
    resize(img_batu, img_batu, cv::Size(), 2, 2);
    resize(img_boad, img_boad, cv::Size(), 5, 5);
    img_boad_clone = img_boad.clone();

    std::cout << "USER Write" << std::endl;
    std::cin >> str_cin;
    std::cout << std::endl;
    str_cin_cv = "USR_write:   " + str_cin; 

    for (auto i = 0; i < str_cin.size(); i++)
    {
        str_test.push_back(str_cin[i]);
    }

    moji_find(str_test, str_real, str_result, str_marubatu);
    moji_find_result(str_result, str_real, str_marubatu);
    moji_kokuban(str_result, str_real, str_marubatu, str_cin_cv, img_boad_clone);
    tudanuma_filter(str_marubatu, img_maru ,img_batu);

    cv::waitKey(0);

    return 0;
}