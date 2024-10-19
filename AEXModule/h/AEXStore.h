#pragma once
#include "File.h"
#include "System.h"
#include "Encryption.h"
typedef struct _AEX_STORE_STRUCT {
	size_t  index;//����λ��
	Byteset token;//��ʶ
	Byteset name;//����
	Byteset data;//����
	int structSize;//�ṹ��С
	long long dataSize;//���ݴ�С
	int updateCount;//�޸Ĵ���
	std::string createTime;//����ʱ�� System::GetTime(true);
	std::string updateTime;//�޸�ʱ�� System::GetTime(true);
} AEX_STORE_STRUCT, *PAEX_STORE_STRUCT;
/*
* version 1.0.0
*/
class AEXStore {
private:
	bool isOpened = false;
	std::string path;
	File file;
public:
	Byteset token;
public:
	/*
	* �����ṹ
	* @param name ����
	* @param data ����
	* @param flag �Ƿ�ɹ�
	* @param structData �ṹ����,Ĭ��ֵΪ��
	* @return ���ؽṹ
	*/
	Byteset createStruct(const Byteset name,const Byteset data,bool& flag,PAEX_STORE_STRUCT structData = NULL) const;
	/*
	* �ҵ�ָ�����ƵĽṹ
	* @param name ����
	* @param flag �Ƿ����
	* @return ���ؽṹ
	*/
	AEX_STORE_STRUCT findStruct(const Byteset name, bool& flag) const;
	/*
	* �ҵ�ָ�����ƵĽṹ
	* @param name ����
	* @param flag �Ƿ����
	* @return ���ؽṹ
	*/
	//AEX_STORE_STRUCT findStruct(const Byteset name, bool& flag) const;
	/*
	* ����ָ�����ƵĽṹ
	* @param name ����
	* @param data ����
	* @return �Ƿ�ɹ�
	*/
	bool updateStruct(const Byteset name,const Byteset data) const;
	/*
	* ɾ��ָ�����ƵĽṹ
	* @param name ����
	* @return �����Ƿ�ɹ�
	*/
	bool deleteStruct(const Byteset name) const;
	/*
	* �����ṹ
	* @param data �ṹ����
	* @param tokenName token����
	* @param index ����,����ṹ�����а������token�ṹ,����Ҫָ������,��0��ʼ
	* @param flag �Ƿ�ɹ�
	* @return ���ؽṹ
	*/
	AEX_STORE_STRUCT analyzeStruct(const Byteset data, Byteset tokenName, int index, bool& flag) const;
	/*
	* ���ݻ�ԭ�ṹ,�����ݽṹ������ݻ�ԭ���ֽڼ�
	* @param data �ṹ����
	* @return �����ֽڼ�
	*/
	Byteset restoreStruct(AEX_STORE_STRUCT data) const;
public:
	AEXStore();
	AEXStore(std::string path,bool create = false);
	~AEXStore();
	// ��ȡ�ֿ�·��
	std::string getPath();
	/*
	* ��ȡ��ǰtoken��ʶ
	*/
	Byteset getToken() const;
	/*
	* ���õ�ǰtoken��ʶ
	*/
	void setToken(Byteset token);
	/*
	* ����ֿ�
	* @param path �ֿ�·��
	* @param create �Ƿ񴴽��ֿ�
	* @return �ɹ�����true��ʧ�ܷ���false
	*/
	bool Load(std::string path, bool create = false);
	/*
	* �ͷŲֿ�
	* @param delFile �Ƿ�ɾ���ļ�
	* @return �ɹ�����true��ʧ�ܷ���false
	*/
	bool Free(bool delFile = false);
	/*
	* д����
	* @param name ����
	* @param data ����
	* @param flag �������򴴽�,Ĭ��false
	* @return �Ƿ�ɹ�
	*/
	bool writeData(const Byteset name,const Byteset data,bool flag = false) const;
	/*
	* ������
	* @param name ����
	* @param data ���ݽṹ
	* @return �Ƿ�ɹ�
	*/
	bool readData(const Byteset name, AEX_STORE_STRUCT& data) const;
	/*
	* ɾ������
	* @param name ����
	* @return �Ƿ�ɹ�
	*/
	bool deleteData(const Byteset name) const;
	/**
	* ȡToken������Key
	* @param tokenName Token����
	* @param pegeNum ҳ��
	* @param pageSize ҳ��С
	* @return ����Key
	*/
	std::vector<Byteset> getAllKeys(const Byteset tokenName, int pegeNum, int pageSize) const;
};