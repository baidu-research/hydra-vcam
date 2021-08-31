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
#ifndef __TIMES_CONSUME__
#define __TIMES_CONSUME__

#include "sysinfo.h"  //PTRACE
#include "includes.h"

static inline double difftimeval(const struct timeval *start, const struct timeval *end)
{
        double d;
        time_t s;
        suseconds_t u;

        s = start->tv_sec - end->tv_sec;
        u = start->tv_usec - end->tv_usec;
        //if (u < 0)
        //        --s;

        d = s;
        d *= 1000000.0;//1 �� = 10^6 ΢��
        d += u;
				d   /=1000.0; //return ms
        return d;
}

class CTimeUsed
{
public:
CTimeUsed(char* name)
{
	gettimeofday(&tv_s,NULL); 
	name_t =name;
}

~CTimeUsed()
{
	 	gettimeofday(&tv_e,NULL);
	 	PTRACE(" %s times cosumed=%.2f",name_t,difftimeval(&tv_e,&tv_s));
}
private:
	struct  timeval  tv_s,tv_e;
	char* name_t;
};
#endif

