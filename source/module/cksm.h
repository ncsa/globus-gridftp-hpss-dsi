/*
 * University of Illinois/NCSA Open Source License
 *
 * Copyright � 2015 NCSA.  All rights reserved.
 *
 * Developed by:
 *
 * Storage Enabling Technologies (SET)
 *
 * Nation Center for Supercomputing Applications (NCSA)
 *
 * http://www.ncsa.illinois.edu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the .Software.),
 * to deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *    + Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *
 *    + Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimers in the
 *      documentation and/or other materials provided with the distribution.
 *
 *    + Neither the names of SET, NCSA
 *      nor the names of its contributors may be used to endorse or promote
 *      products derived from this Software without specific prior written
 *      permission.
 *
 * THE SOFTWARE IS PROVIDED .AS IS., WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 */
#ifndef HPSS_DSI_CKSM_H
#define HPSS_DSI_CKSM_H

/*
 * System includes
 */
#include <openssl/md5.h>

/*
 * Globus includes
 */
#include <globus_gridftp_server.h>

/*
 * HPSS includes
 */
#include <hpss_xml.h>

/*
 * Local includes
 */
#include "commands.h"
#include "config.h"

typedef struct {
  pthread_mutex_t Lock;
  globus_off_t TotalBytes;
  globus_gfs_operation_t Operation;
  globus_callback_handle_t CallbackHandle;
} cksm_marker_t;

typedef struct {
  globus_gfs_operation_t Operation;
  globus_gfs_command_info_t *CommandInfo;
  config_t *Config;
  char *Pathname;
  commands_callback Callback;
  MD5_CTX MD5Context;
  globus_result_t Result;
  int FileFD;
  globus_size_t BlockSize;
  globus_off_t RangeLength;
  cksm_marker_t *Marker;
} cksm_info_t;

void cksm(globus_gfs_operation_t Operation,
          globus_gfs_command_info_t *CommandInfo, config_t *Config,
          commands_callback Callback);

globus_result_t cksm_set_checksum(char *Pathname, config_t *Config,
                                  char *Checksum);

globus_result_t checksum_get_file_sum(char *Pathname, config_t *Config,
                                      char **ChecksumString);

globus_result_t cksm_clear_checksum(char *Pathname, config_t *Config);

#endif /* HPSS_DSI_CKSM_H */
