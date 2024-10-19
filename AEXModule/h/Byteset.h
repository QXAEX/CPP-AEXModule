#pragma once
#include <vector>
#include <string>
#include <iostream>
typedef class Byteset {
public:
    // Ĭ�Ϲ��캯��
    Byteset() = default;

    ~Byteset();

    // ���ַ�������
    Byteset(const std::string& str);

    // ���ֽ����鹹��
    Byteset(const void* bytes, long long size);

    // ���ֽ����鹹��
    Byteset(const char* bytes);

    //��int���͹���
    Byteset(int num);

    //��long���͹���
    Byteset(long num);

    //��long long���͹���
    Byteset(long long num);

    //��size_t���͹���
    Byteset(size_t num);

    //��float���͹���
    Byteset(float num);

    //��double���͹���
    Byteset(double num);

    //��long double���͹���
    Byteset(long double num);

    //��bool���͹���
    Byteset(bool flag);

    //��char���͹���
    Byteset(char ch);

    //��short���͹���
    Byteset(short num);

    // �������캯��
    Byteset(const Byteset& other);

    // �ƶ����캯��
    Byteset(Byteset&& other) noexcept;

    //���ݱȽϴ���
    bool operator==(const Byteset& other) const;

    //���ݲ��ȱȽϴ���
    bool operator!=(const Byteset& other) const;

    // ������ֵ������
    Byteset& operator=(const Byteset& other);

    // ������ֵ������
    Byteset& operator+=(const Byteset& other);
    //������ֵ������:�ı��ַ���
    Byteset& operator=(const std::string& str);

    //������ֵ������:�ֽ�����
    Byteset& operator=(const char* bytes);
    // ������ֵ������
    Byteset& operator=(std::initializer_list<unsigned char> init_list);

    // ��ʼ���б��캯��
    Byteset(std::initializer_list<unsigned char> init_list);

    /*
    * ׷���ֽ�
    * @param bytes �ֽ�����
    * @param size �ֽ������С
    */
    Byteset& append(const void* bytes, long long size);

    // ׷����һ�� Byteset
    Byteset& append(const Byteset& other);

    // ׷���ֽ�
    void push_back(unsigned char byte);

    // �������һ���ֽ�
    unsigned char pop_back();

    // �����ֽ�
    unsigned char& operator[](long long index);

    // �����ֽ�
    const unsigned char& operator[](long long index) const;

    // ��ȡ�ֽڼ���С
    long long size() const;

    // �����ֽڼ���С
    void resize(long long size);
    // �ж��Ƿ�Ϊ��
    bool empty() const;

    // ����ֽڼ�
    void clear();

    /*
    * ��ȡ�ڲ�����ָ��
    * @param index Ҫ��ȡ���ֽڼ�������,Ĭ��ΪNULL,��ʾ��ȡ�����ֽڼ�
    * @return �ֽڼ�����ָ��
    */
    const unsigned char* data(long long index = NULL) const;

    //��׼�����
    friend std::ostream& operator<<(std::ostream& os, const Byteset& byteset);

    /*
    * Ѱ���ֽڼ�
    * @param other ҪѰ�ҵ��ֽڼ�
    * @param pos ��ʼ������λ��
    * @param vague �Ƿ�ģ������,ģ������ʱ,����other����֮ƥ����ֽ�,Ĭ�� ��ģ������
    * @param vagueContent ģ�����ҵĺ����ֽڼ�,Ĭ��Ϊ{0}
    * @return �ҵ���λ�ã����û���ҵ����򷵻�-1
    */
    long long find(const Byteset& other, long long pos = NULL, bool vague = false, const Byteset& vagueContent = nullptr) const;

    /*
    * �滻�ֽڼ�
    * @param old Ҫ�滻���ֽڼ�
    * @param new_str �µ��ֽڼ�
    * @param count �滻����,Ĭ��-1ȫ���滻
    * @param pos ��ʼ������λ��
    * @return ���滻���ֽڼ�����
    */
    long long replace(const Byteset& old, const Byteset& new_str, int count = -1, long long pos = NULL);

    /*
    * �Ƴ��ֽڼ�
    * @param other Ҫ�Ƴ����ֽڼ�
    * @param pos ��ʼ������λ��
    * @param count �Ƴ�����,Ĭ��-1ȫ���Ƴ�
    * @return ���Ƴ����ֽڼ�����
    */
    long long remove(const Byteset& other, long long pos = NULL, int count = -1);

    /*
    * ��ȡ�ֽڼ����Ӽ�
    * @param pos ��ʼλ��
    * @param len �Ӽ�����
    * @return �Ӽ�
    */
    Byteset subBytes(long long pos, long long len) const;

    //�ֽڼ��Ŀ�ʼλ��
    std::vector<unsigned char>::iterator begin();

    //�ֽڼ��Ŀ�ʼλ��
    std::vector<unsigned char>::const_iterator begin() const;

    //�ֽڼ��Ľ���λ��
    std::vector<unsigned char>::iterator end();

    //�ֽڼ��Ľ���λ��
    std::vector<unsigned char>::const_iterator end() const;

    //�ֽڼ�������ʼλ��
    std::vector<unsigned char>::reverse_iterator rbegin();

    //�ֽڼ�������ʼλ��
    std::vector<unsigned char>::const_reverse_iterator rbegin() const;

    //�ֽڼ����������λ��
    std::vector<unsigned char>::reverse_iterator rend();

    //�ֽڼ����������λ��
    std::vector<unsigned char>::const_reverse_iterator rend() const;
private:
    std::vector<unsigned char> data_;
} *LPBYTESET;