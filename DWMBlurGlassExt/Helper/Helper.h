﻿/**
 * FileName: Helper.h
 *
 * Copyright (C) 2024 Maplespe
 *
 * This file is part of MToolBox and DWMBlurGlass.
 * DWMBlurGlass is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or any later version.
 *
 * DWMBlurGlass is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with Foobar.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
*/
#pragma once
#include "../framework.h"
#include "winrt.h"
#include <Uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <dwmapi.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma comment(lib, "dwmapi.lib")

namespace MDWMBlurGlassExt
{
	HRESULT DrawTextWithGlow(
		HDC hdc,
		LPCWSTR pszText,
		int cchText,
		LPRECT prc,
		UINT dwFlags,
		UINT crText,
		UINT crGlow,
		UINT nGlowRadius,
		UINT nGlowIntensity,
		BOOL bPreMultiply,
		DTT_CALLBACK_PROC actualDrawTextCallback,
		LPARAM lParam
	);

	HRESULT DrawThemeContent(
		HDC hdc,
		const RECT& paintRect,
		LPCRECT clipRect,
		LPCRECT excludeRect,
		DWORD additionalFlags,
		std::function<void(HDC, HPAINTBUFFER, RGBQUAD*, int)> callback,
		std::byte alpha = std::byte{ 0xFF },
		bool useBlt = false,
		bool update = true
	);

	HRESULT DrawTextWithAlpha(
		HDC     hdc,
		LPCWSTR lpchText,
		int     cchText,
		LPRECT  lprc,
		UINT    format,
		int& result
	);

	winrt::com_ptr<IWICBitmap> CreateWICBitmap(
		IWICImagingFactory2* factory,
		std::wstring_view filename
	);

	winrt::com_ptr<ID2D1Bitmap1> CreateD2DBitmap(
		IWICImagingFactory2* factory,
		ID2D1DeviceContext* context,
		std::wstring_view filename
	);

	winrt::com_ptr<ID2D1Bitmap1> CreateD2DMaskBitmap(
		ID2D1DeviceContext* context,
		D2D1_SIZE_U size
	);

	HBITMAP CreateAlphaBitmap(int width, int height);

	void EnumMonitors(std::vector<RECT>& monitorRects);

	bool IsRectInside(const RECT& rect1, const RECT& rect2);

	// type = 1, input desktop (grpdeskRitInput)
	// type = 2, default desktop? (grpdeskIODefault)
	// type = 3, unknown
	// type = 4, winlogon desktop (grpdeskLogon)
	// type = ..., desktop created by CreateDesktop?
	bool GetDesktopID(ULONG_PTR type, ULONG_PTR* desktopID);

	bool IsBatterySaverEnabled();

	namespace Vtbl
	{
		struct IWICImagingFactory2Vtbl
		{
			BEGIN_INTERFACE

			DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
			HRESULT(STDMETHODCALLTYPE* QueryInterface)(
				IWICImagingFactory2* This,
				/* [in] */ REFIID riid,
				/* [annotation][iid_is][out] */
				_COM_Outptr_  void** ppvObject);

			DECLSPEC_XFGVIRT(IUnknown, AddRef)
				ULONG(STDMETHODCALLTYPE* AddRef)(
					IWICImagingFactory2* This);

			DECLSPEC_XFGVIRT(IUnknown, Release)
				ULONG(STDMETHODCALLTYPE* Release)(
					IWICImagingFactory2* This);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateDecoderFromFilename)
				HRESULT(STDMETHODCALLTYPE* CreateDecoderFromFilename)(
					IWICImagingFactory2* This,
					/* [in] */ LPCWSTR wzFilename,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [in] */ DWORD dwDesiredAccess,
					/* [in] */ WICDecodeOptions metadataOptions,
					/* [retval][out] */ IWICBitmapDecoder** ppIDecoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateDecoderFromStream)
				HRESULT(STDMETHODCALLTYPE* CreateDecoderFromStream)(
					IWICImagingFactory2* This,
					/* [in] */ IStream* pIStream,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [in] */ WICDecodeOptions metadataOptions,
					/* [retval][out] */ IWICBitmapDecoder** ppIDecoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateDecoderFromFileHandle)
				HRESULT(STDMETHODCALLTYPE* CreateDecoderFromFileHandle)(
					IWICImagingFactory2* This,
					/* [in] */ ULONG_PTR hFile,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [in] */ WICDecodeOptions metadataOptions,
					/* [retval][out] */ IWICBitmapDecoder** ppIDecoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateComponentInfo)
				HRESULT(STDMETHODCALLTYPE* CreateComponentInfo)(
					IWICImagingFactory2* This,
					/* [in] */ REFCLSID clsidComponent,
					/* [out] */ IWICComponentInfo** ppIInfo);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateDecoder)
				HRESULT(STDMETHODCALLTYPE* CreateDecoder)(
					IWICImagingFactory2* This,
					/* [in] */ REFGUID guidContainerFormat,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [retval][out] */ IWICBitmapDecoder** ppIDecoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateEncoder)
				HRESULT(STDMETHODCALLTYPE* CreateEncoder)(
					IWICImagingFactory2* This,
					/* [in] */ REFGUID guidContainerFormat,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [retval][out] */ IWICBitmapEncoder** ppIEncoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreatePalette)
				HRESULT(STDMETHODCALLTYPE* CreatePalette)(
					IWICImagingFactory2* This,
					/* [out] */ IWICPalette** ppIPalette);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateFormatConverter)
				HRESULT(STDMETHODCALLTYPE* CreateFormatConverter)(
					IWICImagingFactory2* This,
					/* [out] */ IWICFormatConverter** ppIFormatConverter);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapScaler)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapScaler)(
					IWICImagingFactory2* This,
					/* [out] */ IWICBitmapScaler** ppIBitmapScaler);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapClipper)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapClipper)(
					IWICImagingFactory2* This,
					/* [out] */ IWICBitmapClipper** ppIBitmapClipper);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFlipRotator)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFlipRotator)(
					IWICImagingFactory2* This,
					/* [out] */ IWICBitmapFlipRotator** ppIBitmapFlipRotator);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateStream)
				HRESULT(STDMETHODCALLTYPE* CreateStream)(
					IWICImagingFactory2* This,
					/* [out] */ IWICStream** ppIWICStream);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateColorContext)
				HRESULT(STDMETHODCALLTYPE* CreateColorContext)(
					IWICImagingFactory2* This,
					/* [out] */ IWICColorContext** ppIWICColorContext);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateColorTransformer)
				HRESULT(STDMETHODCALLTYPE* CreateColorTransformer)(
					IWICImagingFactory2* This,
					/* [out] */ IWICColorTransform** ppIWICColorTransform);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmap)
				HRESULT(STDMETHODCALLTYPE* CreateBitmap)(
					IWICImagingFactory2* This,
					/* [in] */ UINT uiWidth,
					/* [in] */ UINT uiHeight,
					/* [in] */ REFWICPixelFormatGUID pixelFormat,
					/* [in] */ WICBitmapCreateCacheOption option,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFromSource)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFromSource)(
					IWICImagingFactory2* This,
					/* [in] */ IWICBitmapSource* pIBitmapSource,
					/* [in] */ WICBitmapCreateCacheOption option,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFromSourceRect)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFromSourceRect)(
					IWICImagingFactory2* This,
					/* [in] */ IWICBitmapSource* pIBitmapSource,
					/* [in] */ UINT x,
					/* [in] */ UINT y,
					/* [in] */ UINT width,
					/* [in] */ UINT height,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFromMemory)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFromMemory)(
					IWICImagingFactory2* This,
					/* [in] */ UINT uiWidth,
					/* [in] */ UINT uiHeight,
					/* [in] */ REFWICPixelFormatGUID pixelFormat,
					/* [in] */ UINT cbStride,
					/* [in] */ UINT cbBufferSize,
					/* [size_is][in] */ BYTE* pbBuffer,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFromHBITMAP)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFromHBITMAP)(
					IWICImagingFactory2* This,
					/* [in] */ HBITMAP hBitmap,
					/* [unique][in] */ HPALETTE hPalette,
					/* [in] */ WICBitmapAlphaChannelOption options,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateBitmapFromHICON)
				HRESULT(STDMETHODCALLTYPE* CreateBitmapFromHICON)(
					IWICImagingFactory2* This,
					/* [in] */ HICON hIcon,
					/* [out] */ IWICBitmap** ppIBitmap);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateComponentEnumerator)
				HRESULT(STDMETHODCALLTYPE* CreateComponentEnumerator)(
					IWICImagingFactory2* This,
					/* [in] */ DWORD componentTypes,
					/* [in] */ DWORD options,
					/* [out] */ IEnumUnknown** ppIEnumUnknown);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateFastMetadataEncoderFromDecoder)
				HRESULT(STDMETHODCALLTYPE* CreateFastMetadataEncoderFromDecoder)(
					IWICImagingFactory2* This,
					/* [in] */ IWICBitmapDecoder* pIDecoder,
					/* [out] */ IWICFastMetadataEncoder** ppIFastEncoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateFastMetadataEncoderFromFrameDecode)
				HRESULT(STDMETHODCALLTYPE* CreateFastMetadataEncoderFromFrameDecode)(
					IWICImagingFactory2* This,
					/* [in] */ IWICBitmapFrameDecode* pIFrameDecoder,
					/* [out] */ IWICFastMetadataEncoder** ppIFastEncoder);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateQueryWriter)
				HRESULT(STDMETHODCALLTYPE* CreateQueryWriter)(
					IWICImagingFactory2* This,
					/* [in] */ REFGUID guidMetadataFormat,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [out] */ IWICMetadataQueryWriter** ppIQueryWriter);

			DECLSPEC_XFGVIRT(IWICImagingFactory, CreateQueryWriterFromReader)
				HRESULT(STDMETHODCALLTYPE* CreateQueryWriterFromReader)(
					IWICImagingFactory2* This,
					/* [in] */ IWICMetadataQueryReader* pIQueryReader,
					/* [unique][in] */ const GUID* pguidVendor,
					/* [out] */ IWICMetadataQueryWriter** ppIQueryWriter);

			DECLSPEC_XFGVIRT(IWICImagingFactory2, CreateImageEncoder)
				HRESULT(STDMETHODCALLTYPE* CreateImageEncoder)(
					IWICImagingFactory2* This,
					/* [in] */ ID2D1Device* pD2DDevice,
					/* [out] */ IWICImageEncoder** ppWICImageEncoder);

			END_INTERFACE
		};

		interface IWICImagingFactory2
		{
			CONST_VTBL IWICImagingFactory2Vtbl* lpVtbl;
		};
	}
}