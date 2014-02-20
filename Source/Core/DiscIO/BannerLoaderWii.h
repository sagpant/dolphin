// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "DiscIO/BannerLoader.h"

namespace DiscIO
{
class CBannerLoaderWii
	: public IBannerLoader
{
	public:

		CBannerLoaderWii(DiscIO::IVolume *pVolume);

		virtual ~CBannerLoaderWii();

		virtual bool IsValid();

		virtual std::vector<u32> GetBanner(int* pWidth, int* pHeight);

		virtual std::vector<std::string> GetNames();
		virtual std::string GetCompany();
		virtual std::vector<std::string> GetDescriptions();

	private:

		enum
		{
			TEXTURE_SIZE = 192 * 64 * 2,
			ICON_SIZE    = 48 * 48 * 2,
			COMMENT_SIZE = 32
		};

		enum CommentIndex
		{
			NAME_IDX,
			DESC_IDX
		};

		struct SWiiBanner
		{
			u32 ID;

			u32 m_Flag;
			u16 m_Speed;
			u8  m_Unknown[22];

			// Not null terminated!
			u16 m_Comment[2][COMMENT_SIZE];
			u8  m_BannerTexture[TEXTURE_SIZE];
			u8  m_IconTexture[8][ICON_SIZE];
		} ;

		u8* m_pBannerFile;

		bool m_IsValid;

		bool GetStringFromComments(const CommentIndex index, std::string& s);
};
} // namespace
