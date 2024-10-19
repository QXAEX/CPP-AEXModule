#pragma once
#include <string>
#include <vector>
namespace Text {
	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	/*
	* �ı�_�ָ�
	* @param text ���ָ���ı�
	* @param delimiter �ָ���
	* @return �ָ����ı�����
	*/
	std::vector<std::string> text_split(std::string text, std::string delimiter);
	/*
	* �ı�_�ϲ�
	* @param text_list ���ϲ����ı�����
	* @param delimiter �ָ���
	* @return �ϲ�����ı�
	*/
	std::string text_join(std::vector<std::string> text_list, std::string delimiter = "");
	/*
	* �ı�_���ȷָ�
	* @param text ���ָ���ı�
	* @param length �ָ��
	* @return �ָ����ı�����
	*/
	std::vector<std::string> text_split_len(std::string text, size_t length = 1);
	/*
	* �ı�_���ɾ��
	* @param text ��ɾ�����ı�
	* @param length ��ɾ���ĳ���
	* @return ɾ������ı�
	*/
	std::string text_left_del(std::string text, size_t length = 1);
	/*
	* �ı�_�Ҳ�ɾ��
	* @param text ��ɾ�����ı�
	* @param length ��ɾ���ĳ���
	* @return ɾ������ı�
	*/
	std::string text_right_del(std::string text, size_t length = 1);
	/*
	* �ı�_Ѱ��ָ���ı�
	* @param text �����ҵ��ı�
	* @param find_text �����ҵ��ı�
	* @return �ҵ���λ��
	*/
	int text_find(std::string text, std::string find_text);
	/*
	* �ı�_�滻
	* @param text ���滻���ı�
	* @param find_text �����ҵ��ı�
	* @param replace_text �����滻���ı�
	* @param count ����滻������-1��ʾȫ���滻
	* @return �滻����ı�
	*/
	std::string text_replace(std::string text, std::string find_text, std::string replace_text, size_t count = -1);
	/*
	* �ı�_ת���ַ�(��֧������)
	* @param text ��ת�����ı�
	* @return ת������ı�
	*/
	std::wstring text_to_wstr(std::string text);
	/*
	* �ı�_תխ�ַ�(��֧������)
	* @param text ��ת�����ı�
	* @return ת������ı�
	*/
	std::string text_to_str(std::wstring text);
	/*
	* �ı�_ȡ����ַ���(����)
	* @param length �ַ������� (Ĭ��10)
	* @return ����ַ���
	*/
	std::string text_random_num(size_t length = 10);
	/*
	* �ı�_ȡ����ַ���(��ĸ)
	* @param length �ַ������� (Ĭ��10)
	* @return ����ַ���
	*/
	std::string text_random_alpha(size_t length = 10);
	/*
	* �ı�_ȡ����ַ���(��ĸ+����)
	* @param length �ַ������� (Ĭ��10)
	* @return ����ַ���
	*/
	std::string text_random_alnum(size_t length = 10);
	/*
	* �ı�_ȡ����ַ���(��ĸ+����+�����ַ�)
	* @param length �ַ������� (Ĭ��10)
	* @return ����ַ���
	*/
	std::string text_random_special(size_t length = 10);
	//====================================����ת��====================================
	/*
	* �ı�_base64����
	* @param text ��������ı�
	* @return �������ı�
	*/
	std::string text_base64_encode(std::string text);
	/*
	* �ı�_base64����
	* @param text ��������ı�
	* @return �������ı�
	*/
	std::string text_base64_decode(std::string text);
	/*
	* �ı�_GB2312����תUTF8
	* @param text ��ת�����ı�
	* @return ת������ı�
	*/
	std::string text_gb2312_to_utf8(std::string text);
	/*
	* �ı�_UTF8����תGB2312
	* @param text ��ת�����ı�
	* @return ת������ı�
	*/
	std::string text_utf8_to_gb2312(std::string text);
};