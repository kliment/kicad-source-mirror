/*
* This program source code file is part of KICAD, a free EDA CAD application.
*
* Copyright (C) 2016-2017 Kicad Developers, see change_log.txt for contributors.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, you may find one here:
* http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
* or you may search the http://www.gnu.org website for the version 2 license,
* or you may write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

#include <gal/gal_display_options.h>
#include <wx/config.h>

#include <config_map.h>

using namespace KIGFX;

/*
 * Config option strings
 */
static const wxString GalGridStyleConfig( "GridStyle" );
static const wxString GalGridLineWidthConfig( "GridLineWidth" );
static const wxString GalGridMaxDensityConfig( "GridMaxDensity" );
static const wxString GalGridAxesEnabledConfig( "GridAxesEnabled" );
static const wxString GalFullscreenCursorConfig( "CursorFullscreen" );
static const wxString GalForceDisplayCursorConfig( "ForceDisplayCursor" );


static const UTIL::CFG_MAP<KIGFX::GRID_STYLE> gridStyleConfigVals =
{
    { KIGFX::GRID_STYLE::DOTS,       0 },
    { KIGFX::GRID_STYLE::LINES,      1 },
    { KIGFX::GRID_STYLE::SMALL_CROSS,2 },
};


GAL_DISPLAY_OPTIONS::GAL_DISPLAY_OPTIONS()
    : gl_antialiasing_mode( OPENGL_ANTIALIASING_MODE::NONE ),
      cairo_antialiasing_mode( CAIRO_ANTIALIASING_MODE::NONE ),
      m_gridStyle( GRID_STYLE::DOTS ),
      m_gridLineWidth( 1.0 ),
      m_gridMinSpacing( 10.0 ),
      m_axesEnabled( false ),
      m_fullscreenCursor( false ),
      m_forceDisplayCursor( false )
{}


void GAL_DISPLAY_OPTIONS::ReadConfig( wxConfigBase* aCfg, const wxString& aBaseName )
{
    long readLong; // Temp value buffer

    aCfg->Read( aBaseName + GalGridStyleConfig, &readLong,
                static_cast<long>( KIGFX::GRID_STYLE::DOTS ) );
    m_gridStyle = UTIL::GetValFromConfig( gridStyleConfigVals, readLong );

    aCfg->Read( aBaseName + GalGridLineWidthConfig, &m_gridLineWidth, 1.0 );
    aCfg->Read( aBaseName + GalGridMaxDensityConfig, &m_gridMinSpacing, 10 );
    aCfg->Read( aBaseName + GalGridAxesEnabledConfig, &m_axesEnabled, false );
    aCfg->Read( aBaseName + GalFullscreenCursorConfig, &m_fullscreenCursor, false );
    aCfg->Read( aBaseName + GalForceDisplayCursorConfig, &m_forceDisplayCursor, true );

    NotifyChanged();
}


void GAL_DISPLAY_OPTIONS::WriteConfig( wxConfigBase* aCfg, const wxString& aBaseName )
{
    aCfg->Write( aBaseName + GalGridStyleConfig,
                 UTIL::GetConfigForVal( gridStyleConfigVals, m_gridStyle ) );

    aCfg->Write( aBaseName + GalGridLineWidthConfig, m_gridLineWidth );
    aCfg->Write( aBaseName + GalGridMaxDensityConfig, m_gridMinSpacing );
    aCfg->Write( aBaseName + GalGridAxesEnabledConfig, m_axesEnabled );
    aCfg->Write( aBaseName + GalFullscreenCursorConfig, m_fullscreenCursor );
    aCfg->Write( aBaseName + GalForceDisplayCursorConfig, m_forceDisplayCursor );
}


void GAL_DISPLAY_OPTIONS::NotifyChanged()
{
    Notify( &GAL_DISPLAY_OPTIONS_OBSERVER::OnGalDisplayOptionsChanged, *this );
}
