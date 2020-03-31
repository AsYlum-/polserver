#include "vector.h"

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
}  // namespace

bool Vec2d::operator==( const Vec2d& other ) const
{
  return std::tie( _x, _y ) == std::tie( other._x, other._y );
}
bool Vec2d::operator!=( const Vec2d& other ) const
{
  return !( *this == other );
}
bool Vec2d::operator<( const Vec2d& other ) const
{
  return std::tie( _x, _y ) < std::tie( other._x, other._y );
}
bool Vec2d::operator>( const Vec2d& other ) const
{
  return std::tie( _x, _y ) > std::tie( other._x, other._y );
}
bool Vec2d::operator<=( const Vec2d& other ) const
{
  return std::tie( _x, _y ) <= std::tie( other._x, other._y );
}
bool Vec2d::operator>=( const Vec2d& other ) const
{
  return std::tie( _x, _y ) >= std::tie( other._x, other._y );
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

Vec2d operator-( Vec2d lhs, const Vec2d& rhs )
{
  lhs -= rhs;
  return lhs;
}
Vec2d operator+( Vec2d lhs, const Vec2d& rhs )
{
  lhs += rhs;
  return lhs;
}

bool Vec3d::operator==( const Vec3d& other ) const
{
  return std::tie( _xy, _z ) == std::tie( other._xy, other._z );
}
bool Vec3d::operator!=( const Vec3d& other ) const
{
  return !( *this == other );
}
bool Vec3d::operator<( const Vec3d& other ) const
{
  return std::tie( _xy, _z ) < std::tie( other._xy, other._z );
}
bool Vec3d::operator>( const Vec3d& other ) const
{
  return std::tie( _xy, _z ) > std::tie( other._xy, other._z );
}
bool Vec3d::operator<=( const Vec3d& other ) const
{
  return std::tie( _xy, _z ) <= std::tie( other._xy, other._z );
}
bool Vec3d::operator>=( const Vec3d& other ) const
{
  return std::tie( _xy, _z ) >= std::tie( other._xy, other._z );
}
bool Vec3d::operator==( const Vec2d& other ) const
{
  return _xy == other;
}
bool Vec3d::operator!=( const Vec2d& other ) const
{
  return _xy != other;
}
bool Vec3d::operator<( const Vec2d& other ) const
{
  return _xy < other;
}
bool Vec3d::operator>( const Vec2d& other ) const
{
  return _xy > other;
}
bool Vec3d::operator<=( const Vec2d& other ) const
{
  return _xy <= other;
}
bool Vec3d::operator>=( const Vec2d& other ) const
{
  return _xy >= other;
}

Vec3d& Vec3d::operator-=( const Vec3d& other )
{
  _xy -= other._xy;
  int z = static_cast<int>( _z ) - other._z;
  _z = clip_s16( z );
  return *this;
}
Vec3d& Vec3d::operator+=( const Vec3d& other )
{
  _xy += other._xy;
  int z = static_cast<int>( _z ) + other._z;
  _z = clip_s16( z );
  return *this;
}
Vec3d operator-( Vec3d lhs, const Vec3d& rhs )
{
  lhs -= rhs;
  return lhs;
}
Vec3d operator+( Vec3d lhs, const Vec3d& rhs )
{
  lhs += rhs;
  return lhs;
}
}  // namespace Core
}  // namespace Pol
