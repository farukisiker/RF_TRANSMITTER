/*
 * rfid.h
 *
 *  Created on: Nov 23, 2022
 *      Author: mfaruk
 */

#ifndef INC_RFID_H_
#define INC_RFID_H_

void send_rfid_as_char(const char* sCodeWord);
void send_rfid_as_uint32(unsigned long code, unsigned int length);

#endif /* INC_RFID_H_ */
