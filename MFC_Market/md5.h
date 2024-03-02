#if !defined(AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_)
#define AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMD5Crypt
{
private:
	typedef struct {
		UINT  state[4];
		UINT  count[2];
		UCHAR buffer[64];
	} MD5_CTX;

	MD5_CTX* context;

public:
	CMD5Crypt();
	virtual ~CMD5Crypt();

	//c���ӿ�,���ܺ�rfc1321��ԭ�ĵ�ʵ�ִ���ӿ���ͬ

	void Init(void);
	void Update(unsigned char* input, unsigned int inputLen);
	void Final(unsigned char digest[16]);

	//MFC���ӿ�,����ֱ��ʹ��,����Ҫ����Init,Update��Final�ӿ�
	friend class LoginView;

	VOID GetMd5String(OUT CString& strMD5, IN char* input, IN int inputlen);
	VOID GetMd5String(OUT CString& strMD5, IN CString strInput);

private:
	VOID Encode(unsigned char* output, unsigned int* input, unsigned int len);
	VOID Decode(unsigned int* output, unsigned char* input, unsigned int len);
	VOID MD5Transform(unsigned int state[4], unsigned char block[64]);
};

#endif // !defined(AFX_MD5CRYPT_H__8D1E322D_1EF6_4954_A9CF_BAD85BDD1E90__INCLUDED_)
