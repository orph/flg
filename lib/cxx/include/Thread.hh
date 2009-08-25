/*
 * Copyright 2009 Erik Gilling
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __Thread_hh__
#define __Thread_hh__

#include <pthread.h>

class Thread
{
public:
	class Mutex
	{
	private:
		uint8_t _pad0[4096];
		pthread_mutex_t m;
		uint8_t _pad1[4096];
		pthread_mutexattr_t attr;

		void checkPad(void) {
			unsigned int i;
			for (i = 0; i < sizeof(_pad0); i++) {
				if (_pad0[i] != 0x5a)
					printf("_pad0[i] = 0x%02x\n", _pad0[i]);
				if (_pad1[i] != 0xa5)
					printf("_pad1[i] = 0x%02x\n", _pad1[i]);
			}
		}

		void printMutex(void) {
			unsigned int i;

			for (i = 0; i < sizeof(m); i++) {
				printf("%02x ", ((uint8_t *)&m)[i]);
			}
		}

	public:
		Mutex() {
			unsigned int i;
			printf("mutex constructor %08x ", (unsigned int)&m);
			pthread_mutexattr_init(&attr);
			pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
			
//			pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
			printf(" %d\n", pthread_mutex_init(&m, &attr));
			for (i = 0; i < sizeof(m); i++) {
				printf("%02x ", ((uint8_t *)&m)[i]);
			}

			for (i = 0; i < sizeof(m); i++) {
//				printf("%02x ", ((uint8_t *)&mtx)[i]);
			}
			printf("\n");
//			memcpy(&m, &mtx, sizeof(m));
			memset(_pad0, 0x5a, sizeof(_pad0));
			memset(_pad1, 0xa5, sizeof(_pad1));
		}

		~Mutex() {
			printf("mutex destructor %08x\n", (unsigned int)&m);
			pthread_mutex_destroy(&m);
		}

		bool tryLock(void) {
			int err;

			err = pthread_mutex_trylock(&m);
//			printf("trylock %d\n", err);

			return err != 0 ? false : true;
		}

		void lock(void) {
			printf("lock     %08x :",(unsigned int) &m);
			printMutex();
			printf("\n");
//			printf("blocking\n");
			checkPad();
			if (pthread_mutex_lock(&m) != 0) {
				
				printf("lock error\n");
				
				printf("lock error\n");
				
				printf("lock error\n");
				
				printf("lock error\n");
				
				printf("lock error\n");
				
				printf("lock error\n");
				while(1){
				}
			}
			printf("locked   %08x :",(unsigned int) &m);
			printMutex();
			printf("\n");
			checkPad();
		}

		void unlock(void) {
			printf("unlock   %08x: ", (unsigned int)&m);
			printMutex();
			printf("\n");
			checkPad();
			pthread_mutex_unlock(&m);
			printf("unlocked %08x: ", (unsigned int)&m);
			printMutex();
			printf("\n");
			checkPad();
		}
	};

private:
	bool running;
	pthread_t pthread;

	friend void *ThreadStart(void * data);

protected:
	virtual int run(void) = 0;

public:
	Thread();
	virtual ~Thread();

	bool start(void);
	int stop(void);
};


#endif /* __Thread_hh__ */
