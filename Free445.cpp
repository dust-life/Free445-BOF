#include <windows.h>
#include <Lm.h>

extern "C" {
#include "beacon.h"
void go(char* buff, int len);
WINBASEAPI DWORD WINAPI NETAPI32$NetServerTransportEnum(LPWSTR,DWORD,PBYTE*,DWORD,PDWORD,PDWORD,PDWORD);
WINBASEAPI DWORD WINAPI NETAPI32$NetServerTransportDel(LPWSTR,DWORD,PBYTE);
WINBASEAPI DWORD WINAPI NETAPI32$NetApiBufferFree(LPVOID);
WINBASEAPI wchar_t *__cdecl MSVCRT$wcscmp(const wchar_t *_lhs,const wchar_t *_rhs);
}


void go(char * args, int alen) {
	
  if (!BeaconIsAdmin()) {
	BeaconPrintf(CALLBACK_ERROR, "Sorry, You are not Admin !\n");
	return;
  }
	
  wchar_t* transport = L"\\Device\\NetbiosSmb";
  LPSERVER_TRANSPORT_INFO_0 pBuf = NULL;
  LPSERVER_TRANSPORT_INFO_0 pTmpBuf;
  DWORD dwLevel = 0;
  DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
  DWORD dwEntriesRead = 0;
  DWORD dwTotalEntries = 0;
  DWORD dwResumeHandle = 0;
  DWORD dwTotalCount = 0;
  NET_API_STATUS nStatus;
  LPTSTR pszServerName = NULL;
  DWORD i;
  bool found = false;

  do
  {
    // Call the NetServerTransportEnum function; specify level 0.
    nStatus = NETAPI32$NetServerTransportEnum(pszServerName,
      dwLevel,
      (LPBYTE *)&pBuf,
      dwPrefMaxLen,
      &dwEntriesRead,
      &dwTotalEntries,
      &dwResumeHandle);

    if((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
    {
      if((pTmpBuf = pBuf) != NULL)
      {
        // Loop through the entries; process access errors
        for(i = 0; i < dwEntriesRead; i++)
        {
          if(pTmpBuf == NULL)
          {
            BeaconPrintf(CALLBACK_ERROR, "An access violation has occurred\n");
            break;
          }

          // Print the transport protocol name 
          BeaconPrintf(CALLBACK_OUTPUT, "Found Transport: %ls\n", pTmpBuf->svti0_transportname);

          // Delete it if it's the one we want
          if(0 == MSVCRT$wcscmp(pTmpBuf->svti0_transportname, transport))
          {
            NET_API_STATUS status = NETAPI32$NetServerTransportDel(pszServerName, dwLevel, (LPBYTE)pTmpBuf);
            if(NERR_Success == status)
            {
              BeaconPrintf(CALLBACK_OUTPUT, "Deleted %ls\n", transport);
              found = true;
            }
            else BeaconPrintf(CALLBACK_ERROR, "Error %d while deleting %ls\n", status, transport);
          }

          pTmpBuf++;
          dwTotalCount++;
        }
      }
    }
    else BeaconPrintf(CALLBACK_ERROR, "A system error has occurred: %d\n", nStatus);

    // Free the allocated buffer
    if(pBuf != NULL)
    {
      NETAPI32$NetApiBufferFree(pBuf);
      pBuf = NULL;
    }
  } while(nStatus == ERROR_MORE_DATA); // Continue to call NetServerTransportEnum while there are more entries

                                       // Check again for an allocated buffer.
  if(pBuf != NULL) NETAPI32$NetApiBufferFree(pBuf);

  BeaconPrintf(CALLBACK_OUTPUT,"Total of %d entries enumerated\n", dwTotalCount);
}
