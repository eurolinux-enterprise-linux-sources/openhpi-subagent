/*
 * (C) Copyright IBM Corp. 2005
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *   David Judkovics  <djudkovi@us.ibm.com>
 *   Daniel de Araujo <ddearauj@us.ibm.com>
 *
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id: saHpiEventLogInfoTable.h 5405 2005-11-09 22:14:23Z ddearauj $
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIEVENTLOGINFOTABLE_H
#define SAHPIEVENTLOGINFOTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <hpiSubagent.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */

typedef struct saHpiEventLogInfoTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiEventLogInfoEntries;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiEventLogInfoSize;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiEventLogInfoUserEventMaxSize;

        /** SaHpiTime = ASN_OCTET_STR */
            unsigned char saHpiEventLogInfoUpdateTimestamp[SAF_UNSIGNED_64_LEN];
            long saHpiEventLogInfoUpdateTimestamp_len;

        /** SaHpiTime = ASN_OCTET_STR */
            unsigned char saHpiEventLogInfoTime[SAF_UNSIGNED_64_LEN];   
            long saHpiEventLogInfoTime_len;

        /** TruthValue = ASN_INTEGER */
            long saHpiEventLogInfoIsEnabled;

        /** TruthValue = ASN_INTEGER */
            long saHpiEventLogInfoOverflowFlag;

        /** TruthValue = ASN_INTEGER */
            long saHpiEventLogInfoOverflowResetable;

        /** INTEGER = ASN_INTEGER */
            long saHpiEventLogInfoOverflowAction;

        /** INTEGER = ASN_INTEGER */
            long saHpiEventLogInfoOverflowReset;

        /** TruthValue = ASN_INTEGER */
            long saHpiEventLogClear;

        /** TruthValue = ASN_INTEGER */
            long saHpiEventLogState;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiEventLogInfoTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiEventLogInfoTable(void);
void initialize_table_saHpiEventLogInfoTable(void);
const saHpiEventLogInfoTable_context * saHpiEventLogInfoTable_get_by_idx(netsnmp_index *);
const saHpiEventLogInfoTable_context * saHpiEventLogInfoTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiEventLogInfoTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);
/*************************************************************
 * function declarations
 */
SaErrorT populate_saHpiEventLogInfo (SaHpiSessionIdT sessionid);
SaErrorT event_log_info_update (SaHpiSessionIdT sessionid);


/*************************************************************
 * set functions
 */
int event_log_info_time_set (saHpiEventLogInfoTable_context *row_ctx);
int event_info_overflow_reset (saHpiEventLogInfoTable_context *row_ctx);
int event_log_info_clear (saHpiEventLogInfoTable_context *row_ctx);
int event_log_info_state_set (saHpiEventLogInfoTable_context *row_ctx);

/*************************************************************
 * oid declarations
 */
extern oid saHpiEventLogInfoTable_oid[];
extern size_t saHpiEventLogInfoTable_oid_len;

#define saHpiEventLogInfoTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,3,2,1
    
/*************************************************************
 * column number definitions for table saHpiEventLogInfoTable
 */
 
/* Number of table Indexes */
#define EVENT_LOG_INFO_INDEX_NR 2
#define saHpiDomainId_INDEX 0
#define saHpiResourceId_INDEX 1

#define COLUMN_SAHPIEVENTLOGINFOENTRIES 1
#define COLUMN_SAHPIEVENTLOGINFOSIZE 2
#define COLUMN_SAHPIEVENTLOGINFOUSEREVENTMAXSIZE 3
#define COLUMN_SAHPIEVENTLOGINFOUPDATETIMESTAMP 4
#define COLUMN_SAHPIEVENTLOGINFOTIME 5
#define COLUMN_SAHPIEVENTLOGINFOISENABLED 6
#define COLUMN_SAHPIEVENTLOGINFOOVERFLOWFLAG 7
#define COLUMN_SAHPIEVENTLOGINFOOVERFLOWRESETABLE 8
#define COLUMN_SAHPIEVENTLOGINFOOVERFLOWACTION 9
#define COLUMN_SAHPIEVENTLOGINFOOVERFLOWRESET 10
#define COLUMN_SAHPIEVENTLOGCLEAR 11
#define COLUMN_SAHPIEVENTLOGSTATE 12
#define saHpiEventLogInfoTable_COL_MIN 1
#define saHpiEventLogInfoTable_COL_MAX 12

int saHpiEventLogInfoTable_extract_index( saHpiEventLogInfoTable_context * ctx, netsnmp_index * hdr );

void saHpiEventLogInfoTable_set_reserve1( netsnmp_request_group * );
void saHpiEventLogInfoTable_set_reserve2( netsnmp_request_group * );
void saHpiEventLogInfoTable_set_action( netsnmp_request_group * );
void saHpiEventLogInfoTable_set_commit( netsnmp_request_group * );
void saHpiEventLogInfoTable_set_free( netsnmp_request_group * );
void saHpiEventLogInfoTable_set_undo( netsnmp_request_group * );

saHpiEventLogInfoTable_context * saHpiEventLogInfoTable_duplicate_row( saHpiEventLogInfoTable_context* );
netsnmp_index * saHpiEventLogInfoTable_delete_row( saHpiEventLogInfoTable_context* );

int saHpiEventLogInfoTable_can_activate(saHpiEventLogInfoTable_context *undo_ctx,
                      saHpiEventLogInfoTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiEventLogInfoTable_can_deactivate(saHpiEventLogInfoTable_context *undo_ctx,
                        saHpiEventLogInfoTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiEventLogInfoTable_can_delete(saHpiEventLogInfoTable_context *undo_ctx,
                    saHpiEventLogInfoTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
saHpiEventLogInfoTable_context * saHpiEventLogInfoTable_create_row( netsnmp_index* );

saHpiEventLogInfoTable_context * saHpiEventLogInfoTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPIEVENTLOGINFOTABLE_H */
