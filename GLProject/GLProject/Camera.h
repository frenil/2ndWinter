#pragma once
class CCamera
{
private:
	Vec3f m_ptPosition;
	float m_fZoom		{ 1.f };
	Point2f m_ptDelta	{90,0};
	float m_faspect		{ 1.f };
	
public:
	CCamera();
	~CCamera();

	void SetAspect(float aspect) { m_faspect = aspect; LookAt(); }
	void Move(const Vec3f& pt) { m_ptPosition +=pt; LookAt(); }
	void Setposition(const Vec3f& pt) { m_ptPosition = pt; LookAt();}
	const Vec3d& Getposition() const { return m_ptPosition; }
	
	void Rotate(float x, float y){m_ptDelta.x += x; m_ptDelta.y += y; LookAt();}
	void SetDelta(float x, float y) { m_ptDelta.x = x; m_ptDelta.y = y; LookAt();}
	
	Vec3f GetLookVector() const;
	void SetView(int view, Vec3f At);
	void SetZoom(float length) { m_fZoom = length; LookAt(); }
	void LookAt();
	void SetTilte();
	void nZoom(bool In, float length = 0.1f) { m_fZoom += (In ? -1 : 1)*length; LookAt();}
	Vec3f GetPos() { return m_ptPosition; }

};

