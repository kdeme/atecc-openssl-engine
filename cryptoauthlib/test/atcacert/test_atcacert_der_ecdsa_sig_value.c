/** \brief cert ecdsa tests
 *
 * \copyright Copyright (c) 2015 Atmel Corporation. All rights reserved.
 *
 * \atmel_crypto_device_library_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel integrated circuit.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \atmel_crypto_device_library_license_stop
 */



#include "atcacert/atcacert_der.h"
#include "test/unity.h"
#include "test/unity_fixture.h"

TEST_GROUP(atcacert_der_enc_ecdsa_sig_value);

TEST_SETUP(atcacert_der_enc_ecdsa_sig_value)
{
}

TEST_TEAR_DOWN(atcacert_der_enc_ecdsa_sig_value)
{
}

static void atcacert_der_enc_ecdsa_sig_value_test(const uint8_t raw_sig[64], const uint8_t* der_sig_ref, size_t der_sig_ref_size)
{
	int ret;
	uint8_t der_sig[128];
	size_t der_sig_size = sizeof(der_sig);

	ret = atcacert_der_enc_ecdsa_sig_value(raw_sig, der_sig, &der_sig_size);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_SUCCESS, ret, "Expected ATCACERT_E_SUCCESS");
	TEST_ASSERT_EQUAL_MESSAGE(der_sig_ref_size, der_sig_size, "Unexpected der_sig_size");
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(der_sig_ref, der_sig, der_sig_size, "Unexpected der_sig");

	// Size only
	der_sig_size = sizeof(der_sig);
	ret = atcacert_der_enc_ecdsa_sig_value(raw_sig, NULL, &der_sig_size);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_SUCCESS, ret, "Expected ATCACERT_E_SUCCESS");
	TEST_ASSERT_EQUAL_MESSAGE(der_sig_ref_size, der_sig_size, "Unexpected der_sig_size");
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__no_padding)
{
	uint8_t raw_sig[] = {
		0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__r_padding)
{
	uint8_t raw_sig[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2,
		0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99,
		0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__s_padding)
{
	uint8_t raw_sig[] = {
		0x37, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x20, 0x37, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x21, 0x00, 0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__rs_padding)
{
	uint8_t raw_sig[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x49, 0x00, 0x30, 0x46, 0x02, 0x21, 0x00, 0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2,
		0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99,
		0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x21, 0x00, 0xA2, 0xA9, 0xFD, 0xF6, 0x17,
		0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34,
		0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__trim)
{
	uint8_t raw_sig[] = {
		0x00, 0x01, 0xEE, 0x14, 0x70, 0xE4, 0x08, 0xF0, 0x66, 0x0D, 0x9B, 0xED, 0xB0, 0x7B, 0x8C, 0x5B,
		0xCB, 0x1A, 0x1A, 0xB1, 0x61, 0x21, 0xB0, 0xE9, 0x4D, 0x4D, 0x37, 0x7E, 0x9A, 0x12, 0x8F, 0x9A,
		0x00, 0x00, 0x00, 0x02, 0x0F, 0x9C, 0xCE, 0xF6, 0x45, 0xCC, 0xD1, 0x29, 0x97, 0x76, 0xBC, 0x3B,
		0xF4, 0x9D, 0xBC, 0x34, 0x7C, 0x22, 0x96, 0xEA, 0xAF, 0x0C, 0x96, 0x6B, 0xEC, 0x6E, 0xA7, 0x98
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x43, 0x00, 0x30, 0x40, 0x02, 0x1F, 0x01, 0xEE, 0x14, 0x70, 0xE4, 0x08, 0xF0, 0x66, 0x0D,
		0x9B, 0xED, 0xB0, 0x7B, 0x8C, 0x5B, 0xCB, 0x1A, 0x1A, 0xB1, 0x61, 0x21, 0xB0, 0xE9, 0x4D, 0x4D,
		0x37, 0x7E, 0x9A, 0x12, 0x8F, 0x9A, 0x02, 0x1D, 0x02, 0x0F, 0x9C, 0xCE, 0xF6, 0x45, 0xCC, 0xD1,
		0x29, 0x97, 0x76, 0xBC, 0x3B, 0xF4, 0x9D, 0xBC, 0x34, 0x7C, 0x22, 0x96, 0xEA, 0xAF, 0x0C, 0x96,
		0x6B, 0xEC, 0x6E, 0xA7, 0x98
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__trim_all)
{
	uint8_t raw_sig[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	uint8_t der_sig_ref[] = {
		0x03, 0x09, 0x00, 0x30, 0x06, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00
	};

	atcacert_der_enc_ecdsa_sig_value_test(raw_sig, der_sig_ref, sizeof(der_sig_ref));
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__small_buf)
{
	int ret;
	uint8_t der_sig[73];
	size_t der_sig_size = sizeof(der_sig);
	uint8_t raw_sig[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	ret = atcacert_der_enc_ecdsa_sig_value(raw_sig, der_sig, &der_sig_size);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BUFFER_TOO_SMALL, ret, "Expected ATCACERT_E_BUFFER_TOO_SMALL");
	TEST_ASSERT_EQUAL_MESSAGE(74, der_sig_size, "Unexpected der_sig_size");
}

TEST(atcacert_der_enc_ecdsa_sig_value, atcacert_der_enc_ecdsa_sig_value__bad_params)
{
	int ret;
	uint8_t der_sig[128];
	size_t der_sig_size = sizeof(der_sig);
	uint8_t raw_sig[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	ret = atcacert_der_enc_ecdsa_sig_value(NULL, der_sig, &der_sig_size);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");

	ret = atcacert_der_enc_ecdsa_sig_value(NULL, NULL, &der_sig_size);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");

	ret = atcacert_der_enc_ecdsa_sig_value(raw_sig, der_sig, NULL);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");

	ret = atcacert_der_enc_ecdsa_sig_value(NULL, der_sig, NULL);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");

	ret = atcacert_der_enc_ecdsa_sig_value(raw_sig, NULL, NULL);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");

	ret = atcacert_der_enc_ecdsa_sig_value(NULL, NULL, NULL);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_BAD_PARAMS, ret, "Expected ATCACERT_E_BAD_PARAMS");
}

TEST_GROUP(atcacert_der_dec_ecdsa_sig_value);

TEST_SETUP(atcacert_der_dec_ecdsa_sig_value)
{
}

TEST_TEAR_DOWN(atcacert_der_dec_ecdsa_sig_value)
{
}

static void atcacert_der_dec_ecdsa_sig_value_test(const uint8_t* der_sig, size_t der_sig_size, const uint8_t raw_sig_ref[64])
{
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size_ret = der_sig_size;

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size_ret, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_SUCCESS, ret, "Expected ATCACERT_E_SUCCESS");
	TEST_ASSERT_EQUAL_MESSAGE(der_sig_size, der_sig_size_ret, "Unexpected der_int_size_ret");
	TEST_ASSERT_EQUAL_MEMORY_MESSAGE(raw_sig_ref, raw_sig, 64, "Unexpected raw_sig");

	// Size only
	der_sig_size_ret = der_sig_size;
	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size_ret, NULL);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_SUCCESS, ret, "Expected ATCACERT_E_SUCCESS");
	TEST_ASSERT_EQUAL_MESSAGE(der_sig_size, der_sig_size_ret, "Unexpected der_int_size_ret");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__no_padding)
{
	uint8_t raw_sig_ref[] = {
		0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__r_padding)
{
	uint8_t raw_sig_ref[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2,
		0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99,
		0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__s_padding)
{
	uint8_t raw_sig_ref[] = {
		0x37, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x20, 0x37, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x21, 0x00, 0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__rs_padding)
{
	uint8_t raw_sig_ref[] = {
		0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24,
		0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E,
		0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA,
		0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	uint8_t der_sig[] = {
		0x03, 0x49, 0x00, 0x30, 0x46, 0x02, 0x21, 0x00, 0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2,
		0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99,
		0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x21, 0x00, 0xA2, 0xA9, 0xFD, 0xF6, 0x17,
		0xED, 0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34,
		0x37, 0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__trim)
{
	uint8_t raw_sig_ref[] = {
		0x00, 0x01, 0xEE, 0x14, 0x70, 0xE4, 0x08, 0xF0, 0x66, 0x0D, 0x9B, 0xED, 0xB0, 0x7B, 0x8C, 0x5B,
		0xCB, 0x1A, 0x1A, 0xB1, 0x61, 0x21, 0xB0, 0xE9, 0x4D, 0x4D, 0x37, 0x7E, 0x9A, 0x12, 0x8F, 0x9A,
		0x00, 0x00, 0x00, 0x02, 0x0F, 0x9C, 0xCE, 0xF6, 0x45, 0xCC, 0xD1, 0x29, 0x97, 0x76, 0xBC, 0x3B,
		0xF4, 0x9D, 0xBC, 0x34, 0x7C, 0x22, 0x96, 0xEA, 0xAF, 0x0C, 0x96, 0x6B, 0xEC, 0x6E, 0xA7, 0x98
	};
	uint8_t der_sig[] = {
		0x03, 0x43, 0x00, 0x30, 0x40, 0x02, 0x1F, 0x01, 0xEE, 0x14, 0x70, 0xE4, 0x08, 0xF0, 0x66, 0x0D,
		0x9B, 0xED, 0xB0, 0x7B, 0x8C, 0x5B, 0xCB, 0x1A, 0x1A, 0xB1, 0x61, 0x21, 0xB0, 0xE9, 0x4D, 0x4D,
		0x37, 0x7E, 0x9A, 0x12, 0x8F, 0x9A, 0x02, 0x1D, 0x02, 0x0F, 0x9C, 0xCE, 0xF6, 0x45, 0xCC, 0xD1,
		0x29, 0x97, 0x76, 0xBC, 0x3B, 0xF4, 0x9D, 0xBC, 0x34, 0x7C, 0x22, 0x96, 0xEA, 0xAF, 0x0C, 0x96,
		0x6B, 0xEC, 0x6E, 0xA7, 0x98
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__trim_all)
{
	uint8_t raw_sig_ref[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	uint8_t der_sig[] = {
		0x03, 0x09, 0x00, 0x30, 0x06, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00
	};

	atcacert_der_dec_ecdsa_sig_value_test(der_sig, sizeof(der_sig), raw_sig_ref);
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_bs_tag)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[0]++; // Change bit string tag

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_bs_length_low)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[1]--; // Decrement bit string length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_bs_length_high)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[1]++; // Increment bit string length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_bs_extra_data)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28, 0x00
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[1]++; // Increment bit string length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_bs_spare_bits)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[2]++; // Change bit string spare bits

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_seq_tag)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[3]++; // Change sequence tag

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_seq_length_low)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[4]--; // Decrement sequence length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_seq_length_high)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[4]++; // Increment sequence length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_seq_extra_data)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28, 0x00
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[4]++; // Increment sequence length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_rint_tag)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[5]++; // Change integer tag

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_rint_length_low)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[6]--; // Decrement integer length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_rint_length_high)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[6]++; // Increment integer length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_sint_tag)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[39]++; // Change integer tag

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_sint_length_low)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[40]--; // Decrement integer length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_sint_length_high)
{
	uint8_t der_sig[] = {
		0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x01, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED, 0x5C,
		0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37, 0x8F,
		0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[40]++; // Increment integer length

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_rint_too_large)
{
	uint8_t der_sig[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0xA2, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2,
		0x96, 0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99,
		0xB5, 0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x20, 0x37, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[7]++; // Alter padding byte

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}

TEST(atcacert_der_dec_ecdsa_sig_value, atcacert_der_dec_ecdsa_sig_value__bad_sint_too_large)
{
	uint8_t der_sig[] = {
		0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x20, 0x37, 0xB9, 0xB1, 0x0A, 0x5E, 0x15, 0xDF, 0xF2, 0x96,
		0x5B, 0x73, 0xFF, 0x5E, 0x02, 0x16, 0x24, 0x1B, 0xC8, 0x1D, 0x13, 0x80, 0xE8, 0xE9, 0x99, 0xB5,
		0x28, 0xF4, 0xDD, 0x05, 0xBD, 0xE6, 0x8E, 0x02, 0x21, 0x00, 0xA2, 0xA9, 0xFD, 0xF6, 0x17, 0xED,
		0x5C, 0xA4, 0xF7, 0x62, 0x2A, 0x18, 0x61, 0x16, 0x2E, 0xFA, 0x0C, 0x74, 0x64, 0x22, 0x34, 0x37,
		0x8F, 0x40, 0x03, 0x62, 0xB5, 0xDB, 0x04, 0x2A, 0x65, 0x28
	};
	int ret;
	uint8_t raw_sig[64];
	size_t der_sig_size = sizeof(der_sig);

	der_sig[41]++; // Alter padding byte

	ret = atcacert_der_dec_ecdsa_sig_value(der_sig, &der_sig_size, raw_sig);
	TEST_ASSERT_EQUAL_MESSAGE(ATCACERT_E_DECODING_ERROR, ret, "Expected ATCACERT_E_DECODING_ERROR");
}