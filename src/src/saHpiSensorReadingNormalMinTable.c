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
 *       : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id: saHpiSensorReadingNormalMinTable.c 5429 2005-11-14 22:23:12Z ddearauj $
 *
 *
 * For help understanding NET-SNMP in general, please check the 
 *     documentation and FAQ at:
 *
 *     http://www.net-snmp.org/
 *
 *
 * For help understanding this code, the agent and how it processes
 *     requests, please check the following references.
 *
 *     http://www.net-snmp.org/tutorial-5/
 *
 *
 * You can also join the #net-snmp channel on irc.freenode.net
 *     and ask for help there.
 *
 *
 * And if all else fails, send a detailed message to the developers
 *     describing the problem you are having to:
 *
 *    net-snmp-coders@lists.sourceforge.net
 *
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/library/snmp_assert.h>

#include <SaHpi.h>
#include "saHpiSensorReadingNormalMinTable.h"
#include <hpiSubagent.h>
#include <hpiCheckIndice.h>
#include <session_info.h>

#include <oh_utils.h>
#include <hpiLock.h>


static     netsnmp_handler_registration *my_handler = NULL;
static     netsnmp_table_array_callbacks cb;

oid saHpiSensorReadingNormalMinTable_oid[] = { saHpiSensorReadingNormalMinTable_TABLE_OID};
size_t saHpiSensorReadingNormalMinTable_oid_len = OID_LENGTH(saHpiSensorReadingNormalMinTable_oid);

/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/

/*
 * SaErrorT populate_sensor_max()
 */
SaErrorT populate_sensor_normal_min(SaHpiSessionIdT sessionid, 
				    SaHpiRdrT *rdr_entry,
				    SaHpiRptEntryT *rpt_entry)
{

	DEBUGMSGTL ((AGENT, "populate_sensor_normal_min, called\n"));

	SaErrorT rv = SA_OK;
        int new_row = MIB_FALSE;

	oid sensor_normal_min_oid[SENSOR_READING_NORMAL_MIN_INDEX_NR];
	netsnmp_index sensor_normal_min_index;
	saHpiSensorReadingNormalMinTable_context *sensor_normal_min_context;

	/* check for NULL pointers */
	if (!rdr_entry) {
		DEBUGMSGTL ((AGENT, 
			     "ERROR: populate_sensor_normal_min() passed NULL rdr_entry pointer\n"));
		return AGENT_ERR_INTERNAL_ERROR;
	}
	if (!rpt_entry) {
		DEBUGMSGTL ((AGENT, 
			     "ERROR: populate_sensor_normal_min() passed NULL rdr_entry pointer\n"));
		return AGENT_ERR_INTERNAL_ERROR;
	}

	
	subagent_lock(&hpi_lock_data);
	/* BUILD oid for new row */
	/* assign the number of indices */
	sensor_normal_min_index.len = SENSOR_READING_NORMAL_MIN_INDEX_NR;
	/** Index saHpiDomainId is external */
	sensor_normal_min_oid[0] = get_domain_id(sessionid);
	/** Index saHpiResourceId is external */
	sensor_normal_min_oid[1] = rpt_entry->ResourceId;
	/** Index saHpiResourceIsHistorical is external */
	sensor_normal_min_oid[2] = MIB_FALSE;
	/** Index saHpiSensorNum */
	sensor_normal_min_oid[3] = rdr_entry->RdrTypeUnion.SensorRec.Num;
	/* assign the indices to the index */
	sensor_normal_min_index.oids = (oid *) & sensor_normal_min_oid;

	/* See if Row exists. */
	sensor_normal_min_context = NULL;
	sensor_normal_min_context = CONTAINER_FIND(cb.container, &sensor_normal_min_index);

	if (!sensor_normal_min_context) {
		// New entry. Add it
		sensor_normal_min_context = 
		saHpiSensorReadingNormalMinTable_create_row(&sensor_normal_min_index);
                new_row = MIB_TRUE;
	}
	if (!sensor_normal_min_context) {
		snmp_log (LOG_ERR, "Not enough memory for a Normal Min row!");
		subagent_unlock(&hpi_lock_data);
		return AGENT_ERR_INTERNAL_ERROR;
	}

	/** TruthValue = ASN_INTEGER */
	sensor_normal_min_context->saHpiSensorReadingNormalMinIsSupported =
	(rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.NormalMin.IsSupported
	 == SAHPI_TRUE) ? MIB_TRUE : MIB_FALSE;

	/** SaHpiSensorReadingType = ASN_INTEGER */
	sensor_normal_min_context->saHpiSensorReadingNormalMinType = 
	rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.NormalMin.Type + 1;

	/** SaHpiSensorReadingValue = ASN_OCTET_STR */
	sensor_normal_min_context->saHpiSensorReadingNormalMinValue_len =
	set_sensor_reading_value(
				&rdr_entry->RdrTypeUnion.SensorRec.DataFormat.Range.NormalMin,
				sensor_normal_min_context->saHpiSensorReadingNormalMinValue);

	if (new_row == MIB_TRUE)
                CONTAINER_INSERT (cb.container, sensor_normal_min_context);

	subagent_unlock(&hpi_lock_data);
	
	return rv;
}

/**
 * 
 * @domainId
 * @resourceId
 * 
 * @return 
 */
SaErrorT clear_sensor_normal_min(SaHpiDomainIdT domainId, 
                              SaHpiResourceIdT resourceId)

{
        SaErrorT rv = SA_OK;
        netsnmp_index *row_idx;
        saHpiSensorReadingNormalMinTable_context *sen_norm_min_ctx;

	DEBUGMSGTL ((AGENT, "clear_sensor_normal_min, called\n"));	
	DEBUGMSGTL ((AGENT, "           domainId   [%d]\n", domainId));	
	DEBUGMSGTL ((AGENT, "           resourceId [%d]\n", resourceId));

        row_idx = CONTAINER_FIRST(cb.container);
        if (row_idx) //At least one entry was found.
        {
                do {
                        /* based on the found row_idx get the pointer   */
                        /* to its context (row data)                    */
                        sen_norm_min_ctx = CONTAINER_FIND(cb.container, row_idx);

                        /* before we delete the context we should get the  */
                        /* next row (context) if any before we delete this */ 
                        /* one.                                            */
                        row_idx = CONTAINER_NEXT(cb.container, row_idx);

                        if ((sen_norm_min_ctx->index.oids[saHpiSenNormMinDomainId_INDEX] ==
                             domainId) &&

                            (sen_norm_min_ctx->index.oids[saHpiSenNormMinResourceId_INDEX] ==
                             resourceId)) {

                                /* all conditions met remove row */
                                CONTAINER_REMOVE (cb.container, sen_norm_min_ctx);
                                saHpiSensorReadingNormalMinTable_delete_row (sen_norm_min_ctx);
                                DEBUGMSGTL ((AGENT, "clear_sensor_normal_min: "
                                                    "found row: removing\n"));

                        }

                } while (row_idx);
        } 

        return rv;
}


/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/


/************************************************************
 * keep binary tree to find context by name
 */
static int saHpiSensorReadingNormalMinTable_cmp( const void *lhs, const void *rhs );

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiSensorReadingNormalMinTable_cmp( const void *lhs, const void *rhs )
{
	saHpiSensorReadingNormalMinTable_context *context_l =
	(saHpiSensorReadingNormalMinTable_context *)lhs;
	saHpiSensorReadingNormalMinTable_context *context_r =
	(saHpiSensorReadingNormalMinTable_context *)rhs;

	/*
	 * check primary key, then secondary. Add your own code if
	 * there are more than 2 indexes
	 */
	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_cmp, called\n"));

	/* check for NULL pointers */
	if (lhs == NULL || rhs == NULL ) {
		DEBUGMSGTL((AGENT,"saHpiSensorReadingNormalMinTable_cmp() NULL pointer ERROR\n" ));
		return 0;
	}
	/* CHECK FIRST INDEX,  saHpiDomainId */
	if ( context_l->index.oids[0] < context_r->index.oids[0])
		return -1;

	if ( context_l->index.oids[0] > context_r->index.oids[0])
		return 1;

	if ( context_l->index.oids[0] == context_r->index.oids[0]) {
		/* If saHpiDomainId index is equal sort by second index */
		/* CHECK SECOND INDEX,  saHpiResourceEntryId */
		if ( context_l->index.oids[1] < context_r->index.oids[1])
			return -1;

		if ( context_l->index.oids[1] > context_r->index.oids[1])
			return 1;

		if ( context_l->index.oids[1] == context_r->index.oids[1]) {
			/* If saHpiResourceEntryId index is equal sort by third index */
			/* CHECK THIRD INDEX,  saHpiResourceIsHistorical */
			if ( context_l->index.oids[2] < context_r->index.oids[2])
				return -1;

			if ( context_l->index.oids[2] > context_r->index.oids[2])
				return 1;

			if ( context_l->index.oids[2] == context_r->index.oids[2]) {
				/* If saHpiResourceIsHistorical index is equal sort by forth index */
				/* CHECK FORTH INDEX,  saHpiSensorNum */
				if ( context_l->index.oids[3] < context_r->index.oids[3])
					return -1;

				if ( context_l->index.oids[3] > context_r->index.oids[3])
					return 1;

				if ( context_l->index.oids[3] == context_r->index.oids[3])
					return 0;
			}
		}
	}

	return 0;
}


/************************************************************
 * Initializes the saHpiSensorReadingNormalMinTable module
 */
void
init_saHpiSensorReadingNormalMinTable(void)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_cmp, called\n"));

	initialize_table_saHpiSensorReadingNormalMinTable();
}

/************************************************************
 * the *_row_copy routine
 */
static int saHpiSensorReadingNormalMinTable_row_copy(saHpiSensorReadingNormalMinTable_context * dst,
						     saHpiSensorReadingNormalMinTable_context * src)
{
	if (!dst||!src)
		return 1;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_row_copy, called\n"));
        subagent_lock(&hpi_lock_data);

	/*
	 * copy index, if provided
	 */
	if (dst->index.oids)
		free(dst->index.oids);
	if (snmp_clone_mem( (void*)&dst->index.oids, src->index.oids,
			    src->index.len * sizeof(oid) )) {
		dst->index.oids = NULL;
                subagent_unlock(&hpi_lock_data);
		return 1;
	}
	dst->index.len = src->index.len;


	/*
	 * copy components into the context structure
	 */
	/** TODO: add code for external index(s)! */
	dst->saHpiSensorReadingNormalMinIsSupported = src->saHpiSensorReadingNormalMinIsSupported;

	dst->saHpiSensorReadingNormalMinType = src->saHpiSensorReadingNormalMinType;

	memcpy( dst->saHpiSensorReadingNormalMinValue, src->saHpiSensorReadingNormalMinValue, src->saHpiSensorReadingNormalMinValue_len );
	dst->saHpiSensorReadingNormalMinValue_len = src->saHpiSensorReadingNormalMinValue_len;

        subagent_unlock(&hpi_lock_data);
	return 0;
}

/**
 * the *_extract_index routine
 *
 * This routine is called when a set request is received for an index
 * that was not found in the table container. Here, we parse the oid
 * in the the individual index components and copy those indexes to the
 * context. Then we make sure the indexes for the new row are valid.
 */
int
saHpiSensorReadingNormalMinTable_extract_index( saHpiSensorReadingNormalMinTable_context * ctx, netsnmp_index * hdr )
{
	/*
	 * temporary local storage for extracting oid index
	 *
	 * extract index uses varbinds (netsnmp_variable_list) to parse
	 * the index OID into the individual components for each index part.
	 */
	/** TODO: add storage for external index(s)! */
	netsnmp_variable_list var_saHpiDomainId;
	netsnmp_variable_list var_saHpiResourceId;
	netsnmp_variable_list var_saHpiResourceIsHistorical;
	netsnmp_variable_list var_saHpiSensorNum;
	int err;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_extract_index, called\n"));

        subagent_lock(&hpi_lock_data);
	/*
	 * copy index, if provided
	 */
	if (hdr) {
		netsnmp_assert(ctx->index.oids == NULL);
		if (snmp_clone_mem( (void*)&ctx->index.oids, hdr->oids,
				    hdr->len * sizeof(oid) )) {
			subagent_unlock(&hpi_lock_data);
			return -1;
		}
		ctx->index.len = hdr->len;
	}

	/*
	 * initialize variable that will hold each component of the index.
	 * If there are multiple indexes for the table, the variable_lists
	 * need to be linked together, in order.
	 */
	/** TODO: add code for external index(s)! */
	memset( &var_saHpiDomainId, 0x00, sizeof(var_saHpiDomainId) );
	var_saHpiDomainId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiDomainId.next_variable = &var_saHpiResourceId;

	memset( &var_saHpiResourceId, 0x00, sizeof(var_saHpiResourceId) );
	var_saHpiResourceId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiResourceId.next_variable = &var_saHpiResourceIsHistorical;

	memset( &var_saHpiResourceIsHistorical, 0x00, sizeof(var_saHpiResourceIsHistorical) );
	var_saHpiResourceIsHistorical.type = ASN_INTEGER; /* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiResourceIsHistorical.next_variable = &var_saHpiSensorNum;

	memset( &var_saHpiSensorNum, 0x00, sizeof(var_saHpiSensorNum) );
	var_saHpiSensorNum.type = ASN_UNSIGNED;	/* type hint for parse_oid_indexes */
	/** TODO: link this index to the next, or NULL for the last one */
	var_saHpiSensorNum.next_variable = NULL;


	/*
	 * parse the oid into the individual index components
	 */
	err = parse_oid_indexes( hdr->oids, hdr->len, &var_saHpiDomainId );
	if (err == SNMP_ERR_NOERROR) {
		/*
		 * copy index components into the context structure
		 */
		/** skipping external index saHpiDomainId */

		/** skipping external index saHpiResourceId */

		/** skipping external index saHpiResourceIsHistorical */

		/** skipping external index saHpiSensorNum */


		err = saHpiDomainId_check_index(
					       *var_saHpiDomainId.val.integer);
		err = saHpiResourceEntryId_check_index(
						      *var_saHpiResourceId.val.integer);  
		err = saHpiResourceIsHistorical_check_index(
							   *var_saHpiResourceIsHistorical.val.integer);
		err = saHpiSensorNum_check_index(
						*var_saHpiSensorNum.val.integer);
	}

	/*
	 * parsing may have allocated memory. free it.
	 */
	snmp_reset_var_buffers( &var_saHpiDomainId );

	subagent_unlock(&hpi_lock_data);
	return err;
}

/************************************************************
 * the *_can_activate routine is called
 * when a row is changed to determine if all the values
 * set are consistent with the row's rules for a row status
 * of ACTIVE.
 *
 * return 1 if the row could be ACTIVE
 * return 0 if the row is not ready for the ACTIVE state
 */
int saHpiSensorReadingNormalMinTable_can_activate(saHpiSensorReadingNormalMinTable_context *undo_ctx,
						  saHpiSensorReadingNormalMinTable_context *row_ctx,
						  netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_can_activate, called\n"));

	/*
	 * TODO: check for activation requirements here
	 */


	/*
	 * be optimistic.
	 */
	return 1;
}

/************************************************************
 * the *_can_deactivate routine is called when a row that is
 * currently ACTIVE is set to a state other than ACTIVE. If
 * there are conditions in which a row should not be allowed
 * to transition out of the ACTIVE state (such as the row being
 * referred to by another row or table), check for them here.
 *
 * return 1 if the row can be set to a non-ACTIVE state
 * return 0 if the row must remain in the ACTIVE state
 */
int saHpiSensorReadingNormalMinTable_can_deactivate(saHpiSensorReadingNormalMinTable_context *undo_ctx,
						    saHpiSensorReadingNormalMinTable_context *row_ctx,
						    netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_can_deactivate, called\n"));

	/*
	 * TODO: check for deactivation requirements here
	 */
	return 1;
}

/************************************************************
 * the *_can_delete routine is called to determine if a row
 * can be deleted.
 *
 * return 1 if the row can be deleted
 * return 0 if the row cannot be deleted
 */
int saHpiSensorReadingNormalMinTable_can_delete(saHpiSensorReadingNormalMinTable_context *undo_ctx,
						saHpiSensorReadingNormalMinTable_context *row_ctx,
						netsnmp_request_group * rg)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_can_delete, called\n"));

	/*
	 * probably shouldn't delete a row that we can't
	 * deactivate.
	 */
	if (saHpiSensorReadingNormalMinTable_can_deactivate(undo_ctx,row_ctx,rg) != 1)
		return 0;

	/*
	 * TODO: check for other deletion requirements here
	 */
	return 1;
}

/************************************************************
 * the *_create_row routine is called by the table handler
 * to create a new row for a given index. If you need more
 * information (such as column values) to make a decision
 * on creating rows, you must create an initial row here
 * (to hold the column values), and you can examine the
 * situation in more detail in the *_set_reserve1 or later
 * states of set processing. Simple check for a NULL undo_ctx
 * in those states and do detailed creation checking there.
 *
 * returns a newly allocated saHpiSensorReadingNormalMinTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiSensorReadingNormalMinTable_context *
saHpiSensorReadingNormalMinTable_create_row( netsnmp_index* hdr)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_create_row, called\n"));

	saHpiSensorReadingNormalMinTable_context * ctx =
	SNMP_MALLOC_TYPEDEF(saHpiSensorReadingNormalMinTable_context);

	if (!ctx)
		return NULL;

        subagent_lock(&hpi_lock_data);
	/*
	 * TODO: check indexes, if necessary.
	 */
	if (saHpiSensorReadingNormalMinTable_extract_index( ctx, hdr )) {
		free(ctx->index.oids);
		free(ctx);
                subagent_unlock(&hpi_lock_data);
		return NULL;
	}

	/* netsnmp_mutex_init(ctx->lock);
	   netsnmp_mutex_lock(ctx->lock); */

	/*
	 * TODO: initialize any default values here. This is also
	 * first place you really should allocate any memory for
	 * yourself to use.  If you allocated memory earlier,
	 * make sure you free it for earlier error cases!
	 */
	/**
	*/

        subagent_unlock(&hpi_lock_data);
	return ctx;
}

/************************************************************
 * the *_duplicate row routine
 */
saHpiSensorReadingNormalMinTable_context *
saHpiSensorReadingNormalMinTable_duplicate_row( saHpiSensorReadingNormalMinTable_context * row_ctx)
{
	saHpiSensorReadingNormalMinTable_context * dup;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_duplicate_row, called\n"));

	if (!row_ctx)
		return NULL;

        subagent_lock(&hpi_lock_data);
	dup = SNMP_MALLOC_TYPEDEF(saHpiSensorReadingNormalMinTable_context);
	if (!dup){
                subagent_unlock(&hpi_lock_data);
		return NULL;
        }

	if (saHpiSensorReadingNormalMinTable_row_copy(dup,row_ctx)) {
		free(dup);
		dup = NULL;
	}

        subagent_unlock(&hpi_lock_data);
	return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index * saHpiSensorReadingNormalMinTable_delete_row( saHpiSensorReadingNormalMinTable_context * ctx )
{
	/* netsnmp_mutex_destroy(ctx->lock); */

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_delete_row, called\n"));
        subagent_lock(&hpi_lock_data);

	if (ctx->index.oids)
		free(ctx->index.oids);

	/*
	 * TODO: release any memory you allocated here...
	 */

	/*
	 * release header
	 */
	free( ctx );

        subagent_unlock(&hpi_lock_data);
	return NULL;
}


/************************************************************
 * RESERVE is used to check the syntax of all the variables
 * provided, that the values being set are sensible and consistent,
 * and to allocate any resources required for performing the SET.
 * After this stage, the expectation is that the set ought to
 * succeed, though this is not guaranteed. (In fact, with the UCD
 * agent, this is done in two passes - RESERVE1, and
 * RESERVE2, to allow for dependancies between variables).
 *
 * BEFORE calling this routine, the agent will call duplicate_row
 * to create a copy of the row (unless this is a new row; i.e.
 * row_created == 1).
 *
 * next state -> SET_RESERVE2 || SET_FREE
 */
void saHpiSensorReadingNormalMinTable_set_reserve1( netsnmp_request_group *rg )
{
//    saHpiSensorReadingNormalMinTable_context *row_ctx =
//            (saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx =
//            (saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_variable_list *var;
	netsnmp_request_group_item *current;
	int rc;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_reserve1, called\n"));

	/*
	 * TODO: loop through columns, check syntax and lengths. For
	 * columns which have no dependencies, you could also move
	 * the value/range checking here to attempt to catch error
	 * cases as early as possible.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;
		rc = SNMP_ERR_NOERROR;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			rc = SNMP_ERR_GENERR;
			snmp_log(LOG_ERR, "unknown column in "
				 "saHpiSensorReadingNormalMinTable_set_reserve1\n");
		}

		if (rc)
			netsnmp_request_set_error( current->ri, rc );
		rg->status = SNMP_MAX( rg->status, current->ri->status );
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

void saHpiSensorReadingNormalMinTable_set_reserve2( netsnmp_request_group *rg )
{
//    saHpiSensorReadingNormalMinTable_context *row_ctx = (saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx = (saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;
	netsnmp_variable_list *var;
	int rc;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_reserve2, called\n"));

	rg->rg_void = rg->list->ri;

	/*
	 * TODO: loop through columns, check for valid
	 * values and any range constraints.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;
		rc = SNMP_ERR_NOERROR;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}

		if (rc)
			netsnmp_request_set_error( current->ri, rc);
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * Assuming that the RESERVE phases were successful, the next
 * stage is indicated by the action value ACTION. This is used
 * to actually implement the set operation. However, this must
 * either be done into temporary (persistent) storage, or the
 * previous value stored similarly, in case any of the subsequent
 * ACTION calls fail.
 *
 * In your case, changes should be made to row_ctx. A copy of
 * the original row is in undo_ctx.
 */
void saHpiSensorReadingNormalMinTable_set_action( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingNormalMinTable_context *row_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_action, called\n"));

	int            row_err = 0;
        subagent_lock(&hpi_lock_data);

	/*
	 * TODO: loop through columns, copy varbind values
	 * to context structure for the row.
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	if (row_err) {
		netsnmp_request_set_error((netsnmp_request_info*)rg->rg_void,
					       row_err);
	}

        subagent_unlock(&hpi_lock_data);
        return;
}

/************************************************************
 * Only once the ACTION phase has completed successfully, can
 * the final COMMIT phase be run. This is used to complete any
 * writes that were done into temporary storage, and then release
 * any allocated resources. Note that all the code in this phase
 * should be "safe" code that cannot possibly fail (cue
 * hysterical laughter). The whole intent of the ACTION/COMMIT
 * division is that all of the fallible code should be done in
 * the ACTION phase, so that it can be backed out if necessary.
 *
 * BEFORE calling this routine, the agent will update the
 * container (inserting a row if row_created == 1, or removing
 * the row if row_deleted == 1).
 *
 * AFTER calling this routine, the agent will delete the
 * undo_info.
 */
void saHpiSensorReadingNormalMinTable_set_commit( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingNormalMinTable_context *row_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_commit, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * If either of the RESERVE calls fail, the write routines
 * are called again with the FREE action, to release any resources
 * that have been allocated. The agent will then return a failure
 * response to the requesting application.
 *
 * AFTER calling this routine, the agent will delete undo_info.
 */
void saHpiSensorReadingNormalMinTable_set_free( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingNormalMinTable_context *row_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_free, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: 
			break;
			/** We shouldn't get here */
			/** should have been logged in reserve1 */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 * If the ACTION phase does fail (for example due to an apparently
 * valid, but unacceptable value, or an unforeseen problem), then
 * the list of write routines are called again, with the UNDO
 * action. This requires the routine to reset the value that was
 * changed to its previous value (assuming it was actually changed),
 * and then to release any resources that had been allocated. As
 * with the FREE phase, the agent will then return an indication
 * of the error to the requesting application.
 *
 * BEFORE calling this routine, the agent will update the container
 * (remove any newly inserted row, re-insert any removed row).
 *
 * AFTER calling this routing, the agent will call row_copy
 * to restore the data in existing_row from the date in undo_info.
 * Then undo_info will be deleted (or existing row, if row_created
 * == 1).
 */
void saHpiSensorReadingNormalMinTable_set_undo( netsnmp_request_group *rg )
{
	netsnmp_variable_list *var;
//    saHpiSensorReadingNormalMinTable_context *row_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->existing_row;
//    saHpiSensorReadingNormalMinTable_context *undo_ctx = 
// 	(saHpiSensorReadingNormalMinTable_context *)rg->undo_info;
	netsnmp_request_group_item *current;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_set_undo, called\n"));

	/*
	 * loop through columns
	 */
	for ( current = rg->list; current; current = current->next ) {

		var = current->ri->requestvb;

		switch (current->tri->colnum) {

		default: /** We shouldn't get here */
			netsnmp_assert(0); /** why wasn't this caught in reserve1? */
		}
	}

	/*
	 * done with all the columns. Could check row related
	 * requirements here.
	 */
}

/************************************************************
 *
 * Initialize the saHpiSensorReadingNormalMinTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiSensorReadingNormalMinTable(void)
{
	netsnmp_table_registration_info *table_info;

	DEBUGMSGTL ((AGENT, "initialize_table_saHpiSensorReadingNormalMinTable, called\n"));

	if (my_handler) {
		snmp_log(LOG_ERR, "initialize_table_saHpiSensorReadingNormalMinTable_handler called again\n");
		return;
	}

	memset(&cb, 0x00, sizeof(cb));

	/** create the table structure itself */
	table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

	/* if your table is read only, it's easiest to change the
	   HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
	my_handler = netsnmp_create_handler_registration("saHpiSensorReadingNormalMinTable",
							 netsnmp_table_array_helper_handler,
							 saHpiSensorReadingNormalMinTable_oid,
							 saHpiSensorReadingNormalMinTable_oid_len,
							 HANDLER_CAN_RWRITE);

	if (!my_handler || !table_info) {
		snmp_log(LOG_ERR, "malloc failed in "
			 "initialize_table_saHpiSensorReadingNormalMinTable_handler\n");
		return;	/** mallocs failed */
	}

	/***************************************************
	 * Setting up the table's definition
	 */
	/*
	 * TODO: add any external indexes here.
	 */
	/** TODO: add code for external index(s)! */

	/*
	 * internal indexes
	 */
	/** index: saHpiDomainId */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
	/** index: saHpiResourceId */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
	/** index: saHpiResourceIsHistorical */
	netsnmp_table_helper_add_index(table_info, ASN_INTEGER);
	/** index: saHpiSensorNum */
	netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);

	table_info->min_column = saHpiSensorReadingNormalMinTable_COL_MIN;
	table_info->max_column = saHpiSensorReadingNormalMinTable_COL_MAX;

	/***************************************************
	 * registering the table with the master agent
	 */
	cb.get_value = saHpiSensorReadingNormalMinTable_get_value;
	cb.container = netsnmp_container_find("saHpiSensorReadingNormalMinTable_primary:"
					      "saHpiSensorReadingNormalMinTable:"
					      "table_container");

	netsnmp_container_add_index(cb.container,
				    netsnmp_container_find("saHpiSensorReadingNormalMinTable_secondary:"
							   "saHpiSensorReadingNormalMinTable:"
							   "table_container"));
	cb.container->next->compare = saHpiSensorReadingNormalMinTable_cmp;


	cb.can_set = 1;

	cb.create_row = (UserRowMethod*)saHpiSensorReadingNormalMinTable_create_row;

	cb.duplicate_row = (UserRowMethod*)saHpiSensorReadingNormalMinTable_duplicate_row;
	cb.delete_row = (UserRowMethod*)saHpiSensorReadingNormalMinTable_delete_row;
	cb.row_copy = (Netsnmp_User_Row_Operation *)saHpiSensorReadingNormalMinTable_row_copy;

	cb.can_activate = (Netsnmp_User_Row_Action *)saHpiSensorReadingNormalMinTable_can_activate;
	cb.can_deactivate = (Netsnmp_User_Row_Action *)saHpiSensorReadingNormalMinTable_can_deactivate;
	cb.can_delete = (Netsnmp_User_Row_Action *)saHpiSensorReadingNormalMinTable_can_delete;

	cb.set_reserve1 = saHpiSensorReadingNormalMinTable_set_reserve1;
	cb.set_reserve2 = saHpiSensorReadingNormalMinTable_set_reserve2;
	cb.set_action = saHpiSensorReadingNormalMinTable_set_action;
	cb.set_commit = saHpiSensorReadingNormalMinTable_set_commit;
	cb.set_free = saHpiSensorReadingNormalMinTable_set_free;
	cb.set_undo = saHpiSensorReadingNormalMinTable_set_undo;

	DEBUGMSGTL(("initialize_table_saHpiSensorReadingNormalMinTable",
		    "Registering table saHpiSensorReadingNormalMinTable "
		    "as a table array\n"));
	netsnmp_table_container_register(my_handler, table_info, &cb,
					 cb.container, 1);
}

/************************************************************
 * saHpiSensorReadingNormalMinTable_get_value
 *
 * This routine is called for get requests to copy the data
 * from the context to the varbind for the request. If the
 * context has been properly maintained, you don't need to
 * change in code in this fuction.
 */
int saHpiSensorReadingNormalMinTable_get_value(
					      netsnmp_request_info *request,
					      netsnmp_index *item,
					      netsnmp_table_request_info *table_info )
{
	netsnmp_variable_list *var = request->requestvb;
	saHpiSensorReadingNormalMinTable_context *context = (saHpiSensorReadingNormalMinTable_context *)item;

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_get_value, called\n"));

	switch (table_info->colnum) {
	
	case COLUMN_SAHPISENSORREADINGNORMALMINISSUPPORTED:
		/** TruthValue = ASN_INTEGER */
		snmp_set_var_typed_value(var, ASN_INTEGER,
					 (u_char*)&context->saHpiSensorReadingNormalMinIsSupported,
					 sizeof(context->saHpiSensorReadingNormalMinIsSupported) );
		break;

	case COLUMN_SAHPISENSORREADINGNORMALMINTYPE:
		/** SaHpiSensorReadingType = ASN_INTEGER */
		snmp_set_var_typed_value(var, ASN_INTEGER,
					 (u_char*)&context->saHpiSensorReadingNormalMinType,
					 sizeof(context->saHpiSensorReadingNormalMinType) );
		break;

	case COLUMN_SAHPISENSORREADINGNORMALMINVALUE:
		/** SaHpiSensorReadingValue = ASN_OCTET_STR */
		snmp_set_var_typed_value(var, ASN_OCTET_STR,
					 (u_char*)&context->saHpiSensorReadingNormalMinValue,
					 context->saHpiSensorReadingNormalMinValue_len );
		break;

	default: /** We shouldn't get here */
		snmp_log(LOG_ERR, "unknown column in "
			 "saHpiSensorReadingNormalMinTable_get_value\n");
		return SNMP_ERR_GENERR;
	}
	return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiSensorReadingNormalMinTable_get_by_idx
 */
const saHpiSensorReadingNormalMinTable_context *
saHpiSensorReadingNormalMinTable_get_by_idx(netsnmp_index * hdr)
{

	DEBUGMSGTL ((AGENT, "saHpiSensorReadingNormalMinTable_get_by_idx, called\n"));

	return(const saHpiSensorReadingNormalMinTable_context *)
	CONTAINER_FIND(cb.container, hdr );
}


