/*
 * Copyright (c) 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Alan Walendowski, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef ccnxSimpleFileTransferCommon_h
#define ccnxSimpleFileTransferCommon_h

#include <stdint.h>

#include <parc/security/parc_Identity.h>

#include <ccnx/common/ccnx_Name.h>

#include <ccnx/api/ccnx_Portal/ccnx_Portal.h>

/**
 * See ccnxSimpleFileTransferCommon.h for the initilization of these constants.
 */

extern const char *ccnxSimpleFileTransferCommon_TutorialName;

/**
 * The CCNx Name prefix we'll use for the tutorial.
 */
extern const char *ccnxSimpleFileTransferCommon_NamePrefix;

/**
 * The size of a chunk. We break CCNx Content payloads up into pieces of this size.
 * 1200 was chosen as a size that should prevent IP fragmentation of CCNx ContentObject Messages.
 */
extern const uint32_t ccnxSimpleFileTransferCommon_DefaultChunkSize;

/**
 * The string we use for the 'fetch' command.
 */
extern const char *ccnxSimpleFileTransferCommon_CommandFetch;

/**
 * The string we use for the 'list' command.
 */
extern const char *ccnxSimpleFileTransferCommon_CommandList;


/**
 * Creates and returns a new randomly generated Identity, which is required for signing.
 * In a real application, you would actually use a real Identity. The returned instance
 * must eventually be released by calling parcIdentity_Release().
 *
 * @param [in] keystoreName The name of the file to save the new identity.
 * @param [in] keystorePassword The password of the file holding the identity.
 * @param [in] subjectName The name of the owner of the identity.
 *
 *
 * @return A new, randomly generated, PARCIdentity instance.
 */
PARCIdentity *ccnxSimpleFileTransferCommon_CreateAndGetIdentity(const char *keystoreName,
                                                                const char *keystorePassword,
                                                                const char *subjectName);

/**
 * Initialize and return a new instance of CCNxPortalFactory. A randomly generated identity is
 * used to initialize the factory. The returned instance must eventually be released by calling
 * ccnxPortalFactory_Release().
 *
 * @param [in] keystoreName The name of the file to save the new identity.
 * @param [in] keystorePassword The password of the file holding the identity.
 * @param [in] subjectName The name of the owner of the identity.
 *
 * @return A new instance of a CCNxPortalFactory initialized with a randomly created identity.
 */
CCNxPortalFactory *ccnxSimpleFileTransferCommon_SetupPortalFactory(const char *keystoreName,
                                                                   const char *keystorePassword,
                                                                   const char *subjectName);

/**
 * Given a CCNxName instance, return the numeric value of the chunk specified by the Name.
 * The chunk number is contained in the final NameSegment of the Name.
 *
 * @param [in] name A CCNxName instance from which to extract the chunk number.
 * @return The chunk number encoded in the supplied CCNxName instance.
 */
uint64_t ccnxSimpleFileTransferCommon_GetChunkNumberFromName(const CCNxName *name);


/**
 * Given a CCNxName instance, return a new CCNxName that is the same as the original
 * except without the final segment copied. We use this to strip the chunk number from a
 * supplied CCNxName.
 *
 * @param [in] name A CCNxName instance from which to extract the base name.
 * @return A new CCNxName instance that is the same as the original name, but without the final segment.
 */
CCNxName *ccnxSimpleFileTransferCommon_CreateWithBaseName(const CCNxName *name);

/**
 * Given a CCNxName instance, structured for this tutorial, return a string representation
 * of the file name in the CCNxName. For the tutorial, this is located in the second to
 * last CCnxNameSegment in the CCNxName. The string returned here must eventually be freed
 * by calling parcMemory_Deallocate().
 *
 * @param [in] name A CCNxName instance from which to extract the filename.
 * @return A C string representation of the filename encoded in the supplied CCNxName instance.
 */
char *ccnxSimpleFileTransferCommon_CreateFileNameFromName(const CCNxName *name);

/**
 * Given a CCNxName instance, structured for this tutorial, return a string representation
 * of the command string (e.g. "fetch" or "list"). For the tutorial, this is located in the CCnxNameSegment
 * immediately following the domain prefix in the CCNxName. The string returned here must eventually be freed
 * by calling parcMemory_Deallocate().
 *
 * @param [in] name A CCNxName instance from which to extract the filename.
 * @return A C string representation of the filename encoded in the supplied CCNxName instance.
 */
char *ccnxSimpleFileTransferCommon_CreateCommandStringFromName(const CCNxName *name, const CCNxName *domainPrefix);


#endif // ccnxSimpleFileTransferCommon.h
