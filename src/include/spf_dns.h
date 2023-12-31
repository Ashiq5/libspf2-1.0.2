/* 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of either:
 * 
 *   a) The GNU Lesser General Public License as published by the Free
 *      Software Foundation; either version 2.1, or (at your option) any
 *      later version,
 * 
 *   OR
 * 
 *   b) The two-clause BSD license.
 *
 * These licenses can be found with the distribution in the file LICENSES
 */




#ifndef INC_SPF_DNS
#define INC_SPF_DNS


/*
 * This library has the ability to use one or more of any of a number
 * of DNS "layers" to obtain DNS information.  These layers all have
 * compatible APIs, with only minor differences that relate to their
 * specific functions.  So, they can be mixed and matched in any order
 * to do what you want.
 *
 * When you create a new DNS layer, you can (optionally) specify the
 * layer below it.  If the current DNS layer is not able to resolve
 * the query, it will automatically call the lower layer.
 *
 * Some of the DNS layers allow for debugging information to be
 * printed, some do caching, and, of course, some return actual DNS
 * results either by query the network or by looking up the query in a
 * database.
 *
 * For details about each DNS layer, see the appropriate
 * spf_dns_<layer>.h include file.
 *
 *
 * For example, there is a caching DNS layer that saves the compiled
 * SPF records for future use.  While it takes a small amount of time
 * to compile the AOL SPF record, you will more than make up for it by
 * not having to parse the record every time you get a message from
 * AOL.
 * 
 * If you wanted to, you can even run the SPF system without using
 * real DNS lookups at all.  For testing, I used a DNS layer that
 * contained a built-in zone file.  This idea could easily be extended
 * to being able to read the zone file from disk, or to use a database
 * to access information.
 * 
 * One example of what you could do with such a zone file would be to
 * create your own SPF records for the many free-email providers.
 * Depending on whether you layer this local zone file before or after
 * the real DNS lookups, you can either override published SPF
 * records, or you can provide defaults until SPF records are
 * published.
 * 
 */


/*
 * For those who don't have <arpa/nameserv.h>
 */

#if !defined( HAVE_NS_TYPE )

#define	ns_t_invalid	0
#define	ns_t_a		1
#define	ns_t_ns		2
#define	ns_t_cname	5
#define	ns_t_ptr	12
#define	ns_t_mx		15
#define	ns_t_txt	16
#define ns_t_aaaa	28
/* #define ns_t_a6		38 */
#define	ns_t_any        255		/* Wildcard match. */

typedef int	ns_type;
#endif

#ifndef ns_t_invalid
#define	ns_t_invalid	0
#endif


/*
 * For those who don't have <netdb.h>
 */

#if !defined(HAVE_NETDB_H) && !defined(_WIN32)
#define NETDB_SUCCESS	0
#define	HOST_NOT_FOUND 	1		/* NXDOMAIN (authoritative answer)*/
#define	TRY_AGAIN	2		/* SERVFAIL (no authoritative answer)*/
#define	NO_RECOVERY	3		/* invalid/unimplmeneted query	*/
#define	NO_DATA		4		/* host found, but no RR of req type*/
#endif
typedef int SPF_dns_stat_t;




/*
 * bundle up the info needed to use a dns method
 */


void SPF_dns_destroy_config( SPF_dns_config_t spfdcid );


/*
 * helper functions
 */


#ifdef WORDS_BIGENDIAN
#define SPF_IPV4(a,b,c,d) ((unsigned long)((((unsigned long)a)<<24) + (((unsigned long)b)<<16) + (((unsigned long)c)<<8) + (unsigned long)d))
#else
#define SPF_IPV4(a,b,c,d) ((unsigned long)((((unsigned long)d)<<24) + (((unsigned long)c)<<16) + (((unsigned long)b)<<8) + (unsigned long)a))
#endif


#endif
