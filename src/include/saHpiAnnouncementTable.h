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
 * $Id: saHpiAnnouncementTable.h 5405 2005-11-09 22:14:23Z ddearauj $
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIANNOUNCEMENTTABLE_H
#define SAHPIANNOUNCEMENTTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <oh_utils.h> /* For OH_MAX_TEXT_BUFFER_LENGTH */
#include <hpiSubagent.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiAnnouncementEntryId is internal */

typedef struct saHpiAnnouncementTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */
                  
    int sahpi_announcement_annunciator_num_set;
    int sahpi_announcement_severity_set;
    int sahpi_announcement_status_cond_type_set;
    int sahpi_announcement_entitypath_set;
    int sahpi_announcement_sensornum_set;
    int sahpi_announcement_event_state_set;
    int sahpi_announcement_name_set;
    int sahpi_announcement_mid;
    int sahpi_announcement_text_type_set;
    int sahpi_announcement_text_language_set;
    int sahpi_announcement_text;

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiAnnouncementEntryId;

        /** SaHpiInstrumentId = ASN_UNSIGNED */
            unsigned long saHpiAnnouncementAnnunciatorNum;

        /** SaHpiTime = ASN_OCTET_STR */
            unsigned char saHpiAnnouncementTimestamp[SAF_UNSIGNED_64_LEN];
            long saHpiAnnouncementTimestamp_len;

        /** TruthValue = ASN_INTEGER */
            long saHpiAnnouncementAddedByUser;

        /** SaHpiSeverity = ASN_INTEGER */
            long saHpiAnnouncementSeverity;

        /** TruthValue = ASN_INTEGER */
            long saHpiAnnouncementAcknowledged;

        /** SaHpiSeverity = ASN_INTEGER */
            long saHpiAnnouncementAckBySeverity;

        /** INTEGER = ASN_INTEGER */
            long saHpiAnnouncementStatusCondType;

        /** SaHpiEntityPath = ASN_OCTET_STR */
            unsigned char saHpiAnnouncementEntityPath[OH_MAX_TEXT_BUFFER_LENGTH];
            long saHpiAnnouncementEntityPath_len;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiAnnouncementSensorNum;

        /** SaHpiEventState = ASN_OCTET_STR */
            unsigned char saHpiAnnouncementEventState[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiAnnouncementEventState_len;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiAnnouncementName[SA_HPI_MAX_NAME_LENGTH];
            long saHpiAnnouncementName_len;

        /** SaHpiManufacturerId = ASN_UNSIGNED */
            unsigned long saHpiAnnouncementMid;

        /** SaHpiTextType = ASN_INTEGER */
            long saHpiAnnouncementTextType;

        /** SaHpiTextLanguage = ASN_INTEGER */
            long saHpiAnnouncementTextLanguage;

        /** SaHpiText = ASN_OCTET_STR */
            unsigned char saHpiAnnouncementText[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiAnnouncementText_len;

        /** RowStatus = ASN_INTEGER */
            long saHpiAnnouncementDelete;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiAnnouncementTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiAnnouncementTable(void);
void initialize_table_saHpiAnnouncementTable(void);
const saHpiAnnouncementTable_context * saHpiAnnouncementTable_get_by_idx(netsnmp_index *);
const saHpiAnnouncementTable_context * saHpiAnnouncementTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiAnnouncementTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);

/*************************************************************
 * function declarations: OpenHpi
 */
SaErrorT populate_saHpiAnnouncementTable(SaHpiSessionIdT sessionid, 
                                         SaHpiRdrT *rdr_entry,
                                         SaHpiRptEntryT *rpt_entry);

int announcement_add (saHpiAnnouncementTable_context *row_ctx);
int announcement_ack (saHpiAnnouncementTable_context *row_ctx);
int announcement_delete (saHpiAnnouncementTable_context *row_ctx);

void update_announcements (SaHpiSessionIdT sessionid);
int  clear_announcements (void);


/*************************************************************
 * oid declarations
 */
extern oid saHpiAnnouncementTable_oid[];
extern size_t saHpiAnnouncementTable_oid_len;

#define saHpiAnnouncementTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,3,1,32


/*************************************************************
 * defines included from hpiB0101_enums.h
 */
#define SAHPIANNOUNCEMENTDELETE_ACTIVE  	     1
#define SAHPIANNOUNCEMENTDELETE_NOTINSERVICE	     2
#define SAHPIANNOUNCEMENTDELETE_NOTREADY	     3
#define SAHPIANNOUNCEMENTDELETE_CREATEANDGO	     4
#define SAHPIANNOUNCEMENTDELETE_CREATEANDWAIT        5
#define SAHPIANNOUNCEMENTDELETE_DESTROY 	     6
    
/*************************************************************
 * column number definitions for table saHpiAnnouncementTable
 */

#define ANNOUNCEMENT_INDEX_NR 3 
#define saHpiAnnouncementDomainId_INDEX 0
#define saHpiAnnouncementResourceId_INDEX 1
#define saHpiAnnouncementEntryId_INDEX 2

#define COLUMN_SAHPIANNOUNCEMENTENTRYID 1
#define COLUMN_SAHPIANNOUNCEMENTANNUNCIATORNUM 2
#define COLUMN_SAHPIANNOUNCEMENTTIMESTAMP 3
#define COLUMN_SAHPIANNOUNCEMENTADDEDBYUSER 4
#define COLUMN_SAHPIANNOUNCEMENTSEVERITY 5
#define COLUMN_SAHPIANNOUNCEMENTACKNOWLEDGED 6
#define COLUMN_SAHPIANNOUNCEMENTACKBYSEVERITY 7
#define COLUMN_SAHPIANNOUNCEMENTSTATUSCONDTYPE 8
#define COLUMN_SAHPIANNOUNCEMENTENTITYPATH 9
#define COLUMN_SAHPIANNOUNCEMENTSENSORNUM 10
#define COLUMN_SAHPIANNOUNCEMENTEVENTSTATE 11
#define COLUMN_SAHPIANNOUNCEMENTNAME 12
#define COLUMN_SAHPIANNOUNCEMENTMID 13
#define COLUMN_SAHPIANNOUNCEMENTTEXTTYPE 14
#define COLUMN_SAHPIANNOUNCEMENTTEXTLANGUAGE 15
#define COLUMN_SAHPIANNOUNCEMENTTEXT 16
#define COLUMN_SAHPIANNOUNCEMENTDELETE 17
#define saHpiAnnouncementTable_COL_MIN 2
#define saHpiAnnouncementTable_COL_MAX 17

int saHpiAnnouncementTable_extract_index( saHpiAnnouncementTable_context * ctx, netsnmp_index * hdr );

void saHpiAnnouncementTable_set_reserve1( netsnmp_request_group * );
void saHpiAnnouncementTable_set_reserve2( netsnmp_request_group * );
void saHpiAnnouncementTable_set_action( netsnmp_request_group * );
void saHpiAnnouncementTable_set_commit( netsnmp_request_group * );
void saHpiAnnouncementTable_set_free( netsnmp_request_group * );
void saHpiAnnouncementTable_set_undo( netsnmp_request_group * );

saHpiAnnouncementTable_context * saHpiAnnouncementTable_duplicate_row( saHpiAnnouncementTable_context* );
netsnmp_index * saHpiAnnouncementTable_delete_row( saHpiAnnouncementTable_context* );

int saHpiAnnouncementTable_can_activate(saHpiAnnouncementTable_context *undo_ctx,
                      saHpiAnnouncementTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiAnnouncementTable_can_deactivate(saHpiAnnouncementTable_context *undo_ctx,
                        saHpiAnnouncementTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiAnnouncementTable_can_delete(saHpiAnnouncementTable_context *undo_ctx,
                    saHpiAnnouncementTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
saHpiAnnouncementTable_context * saHpiAnnouncementTable_create_row( netsnmp_index* );

saHpiAnnouncementTable_context * saHpiAnnouncementTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPIANNOUNCEMENTTABLE_H */
