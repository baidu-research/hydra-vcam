/*

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <sys/types.h>

#define  NCC_H264_KEY       0x11aa   
#define  OCR_IMG_KEY        0x11bb       
#define  META_DATA_KEY      0x11cc  
#define  OCR_RES_KEY        0x11dd   

#define  BLOCK_NUM      4

typedef struct _SingleFrame
{
    int length;
    char frame[256*1024-4];
}SingleFrame;

#define MAX_OCR_STR_SIZE  80
#define MAX_OCR_NUMS       10
typedef struct _ocr_box
{
	int x[4];
	int y[4];
}ocr_box;

typedef struct _OcrItem
{
    float score;
    ocr_box box;
    char ocr[MAX_OCR_STR_SIZE];
}OcrItem;

typedef struct _Ocr_Items
{
    int num;
    int fps;
    OcrItem item[MAX_OCR_NUMS];
}Ocr_Items;

typedef unsigned long   SHARE_MEM_HANDLE;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//���������ڴ� ������ڷ���keyָ���ڴ�
//���� Ψһkeyid �� 12345,�ڴ��С
//��� �����ڴ������� ,if err return -1
SHARE_MEM_HANDLE shr_open( key_t keyid,int blockSize,int blockNum);

//���룺�ڴ���������������ɹ� 0��ʧ�� -1
int shr_close(SHARE_MEM_HANDLE handle);


//���룺�ڴ�������������ָ�룬����
//������ɹ� 0��ʧ�� -1
int shr_write(SHARE_MEM_HANDLE handle,void* buffer,int nBytes);


//���룺�ڴ�������������ָ�룬����
//������ɹ� 0��ʧ�� -1
int shr_read(SHARE_MEM_HANDLE handle,void* buffer,int nBytes);

int get_shr_size(SHARE_MEM_HANDLE handle);

//clear all buffer that have not read
int shr_reset_size(SHARE_MEM_HANDLE handle);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //#ifndef _CONFIG_H_

