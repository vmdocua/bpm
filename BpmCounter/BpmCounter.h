
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Apr 17 14:53:50 2003
 */
/* Compiler settings for BpmCounter.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __BpmCounter_h__
#define __BpmCounter_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBpmCounterCtl_FWD_DEFINED__
#define __IBpmCounterCtl_FWD_DEFINED__
typedef interface IBpmCounterCtl IBpmCounterCtl;
#endif 	/* __IBpmCounterCtl_FWD_DEFINED__ */


#ifndef ___IBpmCounterCtlEvents_FWD_DEFINED__
#define ___IBpmCounterCtlEvents_FWD_DEFINED__
typedef interface _IBpmCounterCtlEvents _IBpmCounterCtlEvents;
#endif 	/* ___IBpmCounterCtlEvents_FWD_DEFINED__ */


#ifndef __BpmCounterCtl_FWD_DEFINED__
#define __BpmCounterCtl_FWD_DEFINED__

#ifdef __cplusplus
typedef class BpmCounterCtl BpmCounterCtl;
#else
typedef struct BpmCounterCtl BpmCounterCtl;
#endif /* __cplusplus */

#endif 	/* __BpmCounterCtl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IBpmCounterCtl_INTERFACE_DEFINED__
#define __IBpmCounterCtl_INTERFACE_DEFINED__

/* interface IBpmCounterCtl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBpmCounterCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F26C12E-4B11-4EC2-A940-286150CD09C4")
    IBpmCounterCtl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearHistory( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowHistoryPanel( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowHistoryPanel( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Beat( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE KeyBeat( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBpmCounterCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBpmCounterCtl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBpmCounterCtl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBpmCounterCtl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBpmCounterCtl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBpmCounterCtl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBpmCounterCtl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBpmCounterCtl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearHistory )( 
            IBpmCounterCtl * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShowHistoryPanel )( 
            IBpmCounterCtl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ShowHistoryPanel )( 
            IBpmCounterCtl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *About )( 
            IBpmCounterCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetAll )( 
            IBpmCounterCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IBpmCounterCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Beat )( 
            IBpmCounterCtl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *KeyBeat )( 
            IBpmCounterCtl * This);
        
        END_INTERFACE
    } IBpmCounterCtlVtbl;

    interface IBpmCounterCtl
    {
        CONST_VTBL struct IBpmCounterCtlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBpmCounterCtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBpmCounterCtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBpmCounterCtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBpmCounterCtl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBpmCounterCtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBpmCounterCtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBpmCounterCtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBpmCounterCtl_ClearHistory(This)	\
    (This)->lpVtbl -> ClearHistory(This)

#define IBpmCounterCtl_get_ShowHistoryPanel(This,pVal)	\
    (This)->lpVtbl -> get_ShowHistoryPanel(This,pVal)

#define IBpmCounterCtl_put_ShowHistoryPanel(This,newVal)	\
    (This)->lpVtbl -> put_ShowHistoryPanel(This,newVal)

#define IBpmCounterCtl_About(This)	\
    (This)->lpVtbl -> About(This)

#define IBpmCounterCtl_ResetAll(This)	\
    (This)->lpVtbl -> ResetAll(This)

#define IBpmCounterCtl_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IBpmCounterCtl_Beat(This)	\
    (This)->lpVtbl -> Beat(This)

#define IBpmCounterCtl_KeyBeat(This)	\
    (This)->lpVtbl -> KeyBeat(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_ClearHistory_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_ClearHistory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_get_ShowHistoryPanel_Proxy( 
    IBpmCounterCtl * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IBpmCounterCtl_get_ShowHistoryPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_put_ShowHistoryPanel_Proxy( 
    IBpmCounterCtl * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IBpmCounterCtl_put_ShowHistoryPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_About_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_ResetAll_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_ResetAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_Reset_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_Beat_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_Beat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBpmCounterCtl_KeyBeat_Proxy( 
    IBpmCounterCtl * This);


void __RPC_STUB IBpmCounterCtl_KeyBeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBpmCounterCtl_INTERFACE_DEFINED__ */



#ifndef __BpmCounterLib_LIBRARY_DEFINED__
#define __BpmCounterLib_LIBRARY_DEFINED__

/* library BpmCounterLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BpmCounterLib;

#ifndef ___IBpmCounterCtlEvents_DISPINTERFACE_DEFINED__
#define ___IBpmCounterCtlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IBpmCounterCtlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IBpmCounterCtlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8FED0232-10A9-4CE4-B321-CCCA8EB67178")
    _IBpmCounterCtlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IBpmCounterCtlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IBpmCounterCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IBpmCounterCtlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IBpmCounterCtlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IBpmCounterCtlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IBpmCounterCtlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IBpmCounterCtlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IBpmCounterCtlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IBpmCounterCtlEventsVtbl;

    interface _IBpmCounterCtlEvents
    {
        CONST_VTBL struct _IBpmCounterCtlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IBpmCounterCtlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IBpmCounterCtlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IBpmCounterCtlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IBpmCounterCtlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IBpmCounterCtlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IBpmCounterCtlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IBpmCounterCtlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IBpmCounterCtlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BpmCounterCtl;

#ifdef __cplusplus

class DECLSPEC_UUID("9F030198-9A1A-4458-A437-CC0F61E34313")
BpmCounterCtl;
#endif
#endif /* __BpmCounterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


