/*
 * clog.h
 *
 * PostgreSQL transaction-commit-log manager
 *
 * Portions Copyright (c) 1996-2003, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * $PostgreSQL: pgsql/src/include/access/clog.h,v 1.9 2004/07/01 00:51:38 tgl Exp $
 */
#ifndef CLOG_H
#define CLOG_H

#include "access/xlog.h"

/*
 * Possible transaction statuses --- note that all-zeroes is the initial
 * state.
 *
 * A "subcommitted" transaction is a committed subtransaction whose parent
 * hasn't committed or aborted yet.
 */
typedef int XidStatus;

#define TRANSACTION_STATUS_IN_PROGRESS		0x00
#define TRANSACTION_STATUS_COMMITTED		0x01
#define TRANSACTION_STATUS_ABORTED			0x02
#define TRANSACTION_STATUS_SUB_COMMITTED	0x03

/* exported because lwlock.c needs it */
#define NUM_CLOG_BUFFERS	8


extern void TransactionIdSetStatus(TransactionId xid, XidStatus status);
extern XidStatus TransactionIdGetStatus(TransactionId xid);

extern int	CLOGShmemSize(void);
extern void CLOGShmemInit(void);
extern void BootStrapCLOG(void);
extern void StartupCLOG(void);
extern void ShutdownCLOG(void);
extern void CheckPointCLOG(void);
extern void ExtendCLOG(TransactionId newestXact);
extern void TruncateCLOG(TransactionId oldestXact);
extern void clog_zeropage_redo(int pageno);

#endif   /* CLOG_H */
