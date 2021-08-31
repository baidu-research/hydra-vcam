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
#pragma once

#define  INSTALL_FILE "update.ec" 

typedef enum _UPDATE_TYPE
{
	EC_FILE,
	AI_BLOB,
	AI_BIN,
	AI_XML,
}UPDATE_TYPE;

struct update_info
{
	int file_size;
	UPDATE_TYPE file_type;    //0:self install file  1:ai bob file  2:ai xml file
	char AI_name[120];
};

struct enc_param
{
	 int enc_type;//264=h264;265=h265
	 int enc_bps;  
	 int res[6];  //resverd
};


