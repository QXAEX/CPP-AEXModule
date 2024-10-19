#pragma once
#include <string>
#include <vector>
namespace Text {
	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	/*
	* 文本_分割
	* @param text 待分割的文本
	* @param delimiter 分隔符
	* @return 分割后的文本数组
	*/
	std::vector<std::string> text_split(std::string text, std::string delimiter);
	/*
	* 文本_合并
	* @param text_list 待合并的文本数组
	* @param delimiter 分隔符
	* @return 合并后的文本
	*/
	std::string text_join(std::vector<std::string> text_list, std::string delimiter = "");
	/*
	* 文本_长度分割
	* @param text 待分割的文本
	* @param length 分割长度
	* @return 分割后的文本数组
	*/
	std::vector<std::string> text_split_len(std::string text, size_t length = 1);
	/*
	* 文本_左侧删除
	* @param text 待删除的文本
	* @param length 待删除的长度
	* @return 删除后的文本
	*/
	std::string text_left_del(std::string text, size_t length = 1);
	/*
	* 文本_右侧删除
	* @param text 待删除的文本
	* @param length 待删除的长度
	* @return 删除后的文本
	*/
	std::string text_right_del(std::string text, size_t length = 1);
	/*
	* 文本_寻找指定文本
	* @param text 被查找的文本
	* @param find_text 待查找的文本
	* @return 找到的位置
	*/
	int text_find(std::string text, std::string find_text);
	/*
	* 文本_替换
	* @param text 待替换的文本
	* @param find_text 待查找的文本
	* @param replace_text 用作替换的文本
	* @param count 最大替换次数，-1表示全部替换
	* @return 替换后的文本
	*/
	std::string text_replace(std::string text, std::string find_text, std::string replace_text, size_t count = -1);
	/*
	* 文本_转宽字符(不支持中文)
	* @param text 待转换的文本
	* @return 转换后的文本
	*/
	std::wstring text_to_wstr(std::string text);
	/*
	* 文本_转窄字符(不支持中文)
	* @param text 待转换的文本
	* @return 转换后的文本
	*/
	std::string text_to_str(std::wstring text);
	/*
	* 文本_取随机字符串(数字)
	* @param length 字符串长度 (默认10)
	* @return 随机字符串
	*/
	std::string text_random_num(size_t length = 10);
	/*
	* 文本_取随机字符串(字母)
	* @param length 字符串长度 (默认10)
	* @return 随机字符串
	*/
	std::string text_random_alpha(size_t length = 10);
	/*
	* 文本_取随机字符串(字母+数字)
	* @param length 字符串长度 (默认10)
	* @return 随机字符串
	*/
	std::string text_random_alnum(size_t length = 10);
	/*
	* 文本_取随机字符串(字母+数字+特殊字符)
	* @param length 字符串长度 (默认10)
	* @return 随机字符串
	*/
	std::string text_random_special(size_t length = 10);
	//====================================编码转换====================================
	/*
	* 文本_base64编码
	* @param text 待编码的文本
	* @return 编码后的文本
	*/
	std::string text_base64_encode(std::string text);
	/*
	* 文本_base64解码
	* @param text 待解码的文本
	* @return 解码后的文本
	*/
	std::string text_base64_decode(std::string text);
	/*
	* 文本_GB2312编码转UTF8
	* @param text 待转换的文本
	* @return 转换后的文本
	*/
	std::string text_gb2312_to_utf8(std::string text);
	/*
	* 文本_UTF8编码转GB2312
	* @param text 待转换的文本
	* @return 转换后的文本
	*/
	std::string text_utf8_to_gb2312(std::string text);
};