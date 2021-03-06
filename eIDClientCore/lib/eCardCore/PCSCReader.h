/*
 * Copyright (C) 2012 Bundesdruckerei GmbH
 */

#if !defined(__PCSCREDARE_INCLUDED__)
#define __PCSCREDARE_INCLUDED__

#include "IReader.h"
#include "ICardDetector.h"

#include <winscard.h>

/*!
 * @class PCSCReader
 */

class PCSCReader : public IndividualReader
{
	private:
		SCARDHANDLE m_hCard;            // Handle to a card
		DWORD m_dwProtocol;             // Actual used protocol (T1/T0)
		SCARDCONTEXT m_hScardContext;   // Handle to the PCSC subsystem
		DWORD m_ioctl_pace;

	public:
		/*!
		 * @brief Constructor
		 *
		 * This function calls SCardEstablishContext to get a handle
		 * to the PCSC subsystem. The handle is stored in m_hScardContext.
		 */
		PCSCReader(
			const std::string &,
			std::vector<ICardDetector *>&);

		/*!
		 * @brief Destructor
		 *
		 * This function calls SCardReleaseContext to free the handle
		 * to the PCSC subsystem. The handle is stored in m_hScardContext.
		 */
		~PCSCReader(
			void);

		/*!
		 * @brief Open a connection to a card.
		 *
		 * This function calls SCardConnectA to open a connection to a card.
		 * The resulting handle ist stored in m_hCard.
		 *
		 * @return true if success. Otherwise false.
		 */
		bool open(
			void);

		/*!
		 * @brief Closing a card connection.
		 *
		 * This function calls SCardDisconnect to close the card connection.
		 */
		void close(
			void);

		/*!
		 * @brief This command uses SCardTransmit to send a command to the card.
		 */
		std::vector<unsigned char> transceive(
			const std::vector<unsigned char>& cmd);

		/*!
		 *
		 */
		std::vector<BYTE> getATRForPresentCard(
			void);

		bool supportsPACEnative(void);

		PaceOutput establishPACEChannelNative(const PaceInput &);
};

#endif
