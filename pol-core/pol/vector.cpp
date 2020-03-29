#include "vector.h"

#include "mdelta.h"
#include "realms/realm.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <tuple>

namespace Pol
{
namespace Core
{
namespace
{
s16 clip_s16( int v )
{
  return static_cast<s16>(
      std::min( static_cast<int>( std::numeric_limits<s16>::max() ),
                std::max( static_cast<int>( std::numeric_limits<s16>::min() ), v ) ) );
}
u16 clip_u16( int v )
{
  return static_cast<u16>(
      std::max( 0, std::min( static_cast<int>( std::numeric_limits<u16>::max() ), v ) ) );
}
}  // namespace

bool Vec2d::operator==( const Vec2d& other ) const
{
  return std::tie( _x, _y ) == std::tie( other._x, other._y );
}
bool Vec2d::operator!=( const Vec2d& other ) const
{
  return !( *this == other );
}

Vec2d& Vec2d::operator-=( const Vec2d& other )
{
  int x = static_cast<int>( _x ) - other._x;
  int y = static_cast<int>( _y ) - other._y;
  _x = clip_s16( x );
  _y = clip_s16( y );
  return *this;
}
Vec2d& Vec2d::operator+=( const Vec2d& other )
{
  int x = static_cast<int>( _x ) + other._x;
  int y = static_cast<int>( _y ) + other._y;
  _x = clip_s16( x );
  _y = clip_s16( y );
  return *this;
}
bool Pos2d::operator==( const Pos2d& other ) const
{
  return std::tie( _x, _y ) == std::tie( other._x, other._y );
}
bool Pos2d::operator!=( const Pos2d& other ) const
{
  return !( *this == other );
}

Pos2d& Pos2d::operator-=( u16 range )
{
  int x = static_cast<int>( _x ) - range;
  int y = static_cast<int>( _y ) - range;
  _x = static_cast<u16>( std::max( 0, x ) );
  _y = static_cast<u16>( std::max( 0, y ) );
  return *this;
}
Pos2d& Pos2d::operator+=( u16 range )
{
  int x = static_cast<int>( _x ) + range;
  int y = static_cast<int>( _y ) + range;
  _x = static_cast<u16>( std::min( static_cast<int>( std::numeric_limits<u16>::max() ), x ) );
  _y = static_cast<u16>( std::min( static_cast<int>( std::numeric_limits<u16>::max() ), y ) );
  return *this;
}
Pos2d& Pos2d::operator-=( const Vec2d& other )
{
  int x = static_cast<int>( _x ) - other.x();
  int y = static_cast<int>( _y ) - other.y();
  _x = clip_u16( x );
  _y = clip_u16( y );
  return *this;
}
Pos2d& Pos2d::operator+=( const Vec2d& other )
{
  int x = static_cast<int>( _x ) + other.x();
  int y = static_cast<int>( _y ) + other.y();
  _x = clip_u16( x );
  _y = clip_u16( y );
  return *this;
}
Pos2d operator-( Pos2d lhs, u16 rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos2d operator+( Pos2d lhs, u16 rhs )
{
  lhs += rhs;
  return lhs;
}
Vec2d operator-( const Pos2d& lhs, const Pos2d& rhs )
{
  int x = static_cast<int>( lhs.x() ) - rhs.x();
  int y = static_cast<int>( lhs.y() ) - rhs.y();
  return Vec2d( clip_s16( x ), clip_s16( y ) );
}
Pos2d operator-( Pos2d lhs, const Vec2d& rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos2d operator+( Pos2d lhs, const Vec2d& rhs )
{
  lhs += rhs;
  return lhs;
}

u16 Pos2d::pol_distance( const Pos2d& other ) const
{
  int xd = std::abs( static_cast<int>( _x ) - other._x );
  int yd = std::abs( static_cast<int>( _y ) - other._y );
  return static_cast<u16>( std::max( xd, yd ) );
}


bool Pos3d::operator==( const Pos3d& other ) const
{
  return std::tie( _xy, _z ) == std::tie( other._xy, other._z );
}
bool Pos3d::operator!=( const Pos3d& other ) const
{
  return !( *this == other );
}

Pos3d& Pos3d::operator-=( u16 range )
{
  _xy -= range;
  return *this;
}
Pos3d& Pos3d::operator+=( u16 range )
{
  _xy += range;
  return *this;
}
Pos3d& Pos3d::operator-=( const Vec2d& other )
{
  _xy -= other;
  return *this;
}
Pos3d& Pos3d::operator+=( const Vec2d& other )
{
  _xy += other;
  return *this;
}

Pos3d operator-( Pos3d lhs, u16 rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos3d operator+( Pos3d lhs, u16 rhs )
{
  lhs += rhs;
  return lhs;
}
Pos3d operator-( Pos3d lhs, const Vec2d& rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos3d operator+( Pos3d lhs, const Vec2d& rhs )
{
  lhs += rhs;
  return lhs;
}
Vec2d operator-( const Pos3d& lhs, const Pos2d& rhs )
{
  return lhs.pos2d() - rhs;
}
Vec2d operator-( const Pos3d& lhs, const Pos3d& rhs )
{
  return lhs.pos2d() - rhs.pos2d();
}

u16 Pos3d::pol_distance( const Pos3d& other ) const
{
  return _xy.pol_distance( other._xy );
}


void Pos4d::crop()
{
  if ( _realm == nullptr )
    return;
  if ( x() >= _realm->width() )
    x( _realm->width() - 1 );
  if ( y() >= _realm->height() )
    y( _realm->height() - 1 );
}
u16 Pos4d::cropX( u16 x ) const
{
  if ( _realm != nullptr && x >= _realm->width() )
    return _realm->width() - 1;
  return x;
}
u16 Pos4d::cropY( u16 y ) const
{
  if ( _realm != nullptr && y >= _realm->height() )
    return _realm->height() - 1;
  return y;
}

bool Pos4d::operator==( const Pos4d& other ) const
{
  return std::tie( _xyz, _realm ) == std::tie( other._xyz, other._realm );
}
bool Pos4d::operator==( const Pos3d& other ) const
{
  return _xyz == other;
}
bool Pos4d::operator!=( const Pos4d& other ) const
{
  return !( *this == other );
}
bool Pos4d::operator!=( const Pos3d& other ) const
{
  return !( *this == other );
}

Pos4d& Pos4d::operator-=( u16 range )
{
  _xyz -= range;
  return *this;
}
Pos4d& Pos4d::operator+=( u16 range )
{
  _xyz += range;
  crop();
  return *this;
}

Pos4d& Pos4d::operator-=( const Vec2d& other )
{
  _xyz -= other;
  crop();
  return *this;
}
Pos4d& Pos4d::operator+=( const Vec2d& other )
{
  _xyz += other;
  crop();
  return *this;
}

Pos4d operator-( Pos4d lhs, u16 rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos4d operator+( Pos4d lhs, u16 rhs )
{
  lhs += rhs;
  return lhs;
}
Pos4d operator-( Pos4d lhs, const Vec2d& rhs )
{
  lhs -= rhs;
  return lhs;
}
Pos4d operator+( Pos4d lhs, const Vec2d& rhs )
{
  lhs += rhs;
  return lhs;
}
Vec2d operator-( const Pos4d& lhs, const Pos2d& rhs )
{
  return lhs.pos3d() - rhs;
}
Vec2d operator-( const Pos4d& lhs, const Pos3d& rhs )
{
  return lhs.pos3d() - rhs;
}
Vec2d operator-( const Pos4d& lhs, const Pos4d& rhs )
{
  return lhs.pos3d() - rhs.pos3d();
}

void Pos4d::move( Plib::UFACING dir )
{
  // TODO: move_delta should be a Vec2d
  _xyz += Vec2d( Core::move_delta[dir].xmove, Core::move_delta[dir].ymove );
  crop();
}

u16 Pos4d::pol_distance( const Pos4d& other ) const
{
  if ( _realm != other._realm )
    return std::numeric_limits<u16>::max();
  return _xyz.pol_distance( other._xyz );
}
bool Pos4d::inRange( const Pos4d& other, u16 range ) const
{
  return _realm == other._realm && _xyz.pol_distance( other._xyz ) <= range;
}
bool Pos4d::inRange( const Pos3d& other, u16 range ) const
{
  return _xyz.pol_distance( other ) <= range;
}


}  // namespace Core
}  // namespace Pol
