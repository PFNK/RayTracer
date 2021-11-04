/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"
#include "core/RayHitStructs.h"
#include <vector>


namespace rt
{

	class BlinnPhong : public Material
	{
	public:
		//
		// Constructors
		//
		BlinnPhong();
		// BlinnPhong(Vec3f diffusecolor);
		// ka * ia + for each light: kd(L_m * N)*id_m  + ks(R_m * V)^exponent * is_m
		// ^ ambient + sum(m in light) diffuse_m + specular_m
		// R is mirror reflection direction
		BlinnPhong(float ks, float kd, float kr, float specularexponent, Vec3f diffusecolor, std::vector<Vec3f> texture, int tWidth, int tHeight) : ks(ks), kd(kd), kr(kr), specularexponent(specularexponent), diffusecolor(diffusecolor), texture(texture), tWidth(tWidth), tHeight(tHeight) 
		{
			// printf("creating blinnphong %f %f %f \n", diffusecolor[0], diffusecolor[1], diffusecolor[2]);

			// this->diffusecolor = diffusecolor;
		}

		//
		//Destructor
		//
		virtual ~BlinnPhong();

		Vec3f getColor(Vec3f diffuse, float specular, Vec3f is, float dist, Vec2f uv){
			Vec3f baseColor;
			if(uv.x != -1 && hasTexture){
				//GET TEXTUREs
				int u = uv.x * tWidth;
				int v = uv.y * tHeight;
				baseColor = texture[u + (v*tWidth)];
			}
			else{
				baseColor = diffusecolor;
			}

			Vec3f dif = kd * diffuse * baseColor;
			Vec3f spec = (ks * std::pow(specular,(specularexponent))) * is;
			return ((dif/=dist) + (spec/=dist));
		}
		
		Vec3f getAmbientColor(){
			return diffusecolor;
		}

		float getReflectness(){
			return kr;
		}

	private:
		float ks;
		float kd;
		float kr;
		float specularexponent;
		Vec3f diffusecolor;
		std::vector<Vec3f> texture;
		int tWidth;
		int tHeight;
	};

} //namespace rt

#endif /* BLINNPHONG_H_ */
