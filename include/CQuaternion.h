#ifndef CQUATERNION_H
#define CQUATERNION_H
#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

class vector3f
{
	public:
		float x;
		float y;
		float z;

		vector3f () {}
		vector3f (const vector3f &v) : x(v.x), y(v.y) , z(v.z) {}
		vector3f (float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}

		//! function call operator
		void operator () (const float x0,const float y0, const float z0)
		{	x= x0; y= y0; z= z0;  }

		//! test for equality
		bool operator==(const vector3f &v)
		{	return (x==v.x && y==v.y && z==v.z);	}

		//! test for inequality
		bool operator!=(const vector3f &v)
		{	return (x!=v.x || y!=v.y || z!=v.z);	}

		//! set to value
		const vector3f &operator =(const vector3f &v)
		{
			x= v.x; y= v.y;	z= v.z;
			return *this;
		}

		//! negation
		const vector3f operator -(void) const
		{	return vector3f(-x,-y,-z);	}

		//! addition
		const vector3f operator +(const vector3f &v) const
		{   return vector3f(x+v.x, y+v.y, z+v.z);	 }

		//! subtraction
		const vector3f operator -(const vector3f &v) const
		{   return vector3f(x-v.x, y-v.y, z-v.z);	 }

		//! uniform scaling
		const vector3f operator *(const float num) const
		{
			vector3f temp(*this);
			return temp*=num;
		}

		//! uniform scaling
		const vector3f operator /(const float num) const
		{
			vector3f temp(*this);
			return temp/=num;
		}

		//! addition
		const vector3f &operator +=(const vector3f &v)
		{
			x+=v.x;	y+=v.y;	z+=v.z;
			return *this;
		}

		//! subtraction
		const vector3f &operator -=(const vector3f &v)
		{
			x-=v.x;	y-=v.y;	z-=v.z;
			return *this;
		}

		//! uniform scaling
		const vector3f &operator *=(const float num)
		{
			x*=num; y*=num; z*=num;
			return *this;
		}

		//! uniform scaling
		const vector3f &operator /=(const float num)
		{
			x/=num; y/=num; z/=num;
			return *this;
		}

		//! dot product
		float operator *(const vector3f &v) const
		{	return x*v.x + y*v.y + z*v.z;	}

		//! cross product
		const vector3f operator %(const vector3f &v) const
		{
			vector3f temp(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
			return temp;
		}

		float length_squared() const
		{	return (float)(*this * *this);   }

		float length() const
		{	return (float)sqrt(*this * *this);   }

		//! normalizes this vector
		void normalize()
		{	*this/=length();	}

		//! returns the normalized version of this vector
		vector3f normalized() const
		{   return  *this/length();  }

		//! reflects this vector about n
		void reflect(const vector3f &n)
		{
			vector3f orig(*this);
			project(n);
			*this= *this*2 - orig;
		}

		//! projects this vector onto v
		void project(const vector3f &v)
		{	*this= v * (*this * v)/(v*v);	}

		//! returns this vector projected onto v
		vector3f projected(const vector3f &v)
		{   return v * (*this * v)/(v*v);	}

		//! computes the angle between 2 arbitrary vectors
		static inline float angle(const vector3f &v1, const vector3f &v2)
		{   return acosf((v1*v2) / (v1.length()*v2.length()));  }

		//! computes the angle between 2 arbitrary normalized vectors
		static inline float angle_normalized(const vector3f &v1, const vector3f &v2)
		{   return acosf(v1*v2);  }

};

class CQuaternion
{
	public:

		float s; //!< the real component
		vector3f v; //!< the imaginary components

		CQuaternion (float real, float x, float y, float z): s(real), v(x,y,z) {}
		CQuaternion(float real, const vector3f &i): s(real), v(i) {}
		CQuaternion (float theta_z, float theta_y, float theta_x)
		{
			float cos_z_2 = cosf(0.5f*theta_z);
			float cos_y_2 = cosf(0.5f*theta_y);
			float cos_x_2 = cosf(0.5f*theta_x);

			float sin_z_2 = sinf(0.5f*theta_z);
			float sin_y_2 = sinf(0.5f*theta_y);
			float sin_x_2 = sinf(0.5f*theta_x);

			// and now compute quaternion
			s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
		}

		//! from 3 euler angles
		CQuaternion(const vector3f &angles)
		{
			float cos_z_2 = cosf(0.5f*angles.z);
			float cos_y_2 = cosf(0.5f*angles.y);
			float cos_x_2 = cosf(0.5f*angles.x);

			float sin_z_2 = sinf(0.5f*angles.z);
			float sin_y_2 = sinf(0.5f*angles.y);
			float sin_x_2 = sinf(0.5f*angles.x);

			// and now compute quaternion
			s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
		}

		//! basic operations
		CQuaternion &operator =(const CQuaternion &q)
		{	s= q.s; v= q.v;	return *this;		}

		const CQuaternion operator +(const CQuaternion &q) const
		{	return CQuaternion(s+q.s, v+q.v);	}

		const CQuaternion operator -(const CQuaternion &q) const
		{	return CQuaternion(s-q.s, v-q.v);	}

		const CQuaternion operator *(const CQuaternion &q) const
		{	return CQuaternion(s*q.s - v*q.v,
						  v.y*q.v.z - v.z*q.v.y + s*q.v.x + v.x*q.s,
						  v.z*q.v.x - v.x*q.v.z + s*q.v.y + v.y*q.s,
						  v.x*q.v.y - v.y*q.v.x + s*q.v.z + v.z*q.s);
		}
		//! returns the euler angles from a rotation quaternion
		vector3f euler_angles(bool homogenous=true) const
		{
			float sqw = s*s;
			float sqx = v.x*v.x;
			float sqy = v.y*v.y;
			float sqz = v.z*v.z;

			vector3f euler;
			if (homogenous) {
				euler.x = 3600 * (atan2f(2.f * (v.x*v.y + v.z*s), sqx - sqy - sqz + sqw) / (2*M_PI));
				euler.y = 3600 * (asinf(-2.f * (v.x*v.z - v.y*s))/ (2*M_PI));
				euler.z = 3600 * (atan2f(2.f * (v.y*v.z + v.x*s), -sqx - sqy + sqz + sqw) / (2*M_PI));
			} else {
				euler.x = atan2f(2.f * (v.z*v.y + v.x*s), 1 - 2*(sqx + sqy));
				euler.y = asinf(-2.f * (v.x*v.z - v.y*s));
				euler.z = atan2f(2.f * (v.x*v.y + v.z*s), 1 - 2*(sqy + sqz));
			}
			return euler;
		}
};

#endif
