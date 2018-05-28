#pragma once
#include "stdafx.h"
#include "ResourceManager.h"

void ResourceManager::DefineTriangle()
{
	sf::Vertex a;
	sf::Vertex b;
	sf::Vertex c;

	a.position = sf::Vector2f(0, 0);
	b.position = sf::Vector2f(50, 0);
	c.position = sf::Vector2f(50, 50);

	a.color = sf::Color::Green;
	b.color = sf::Color::Blue;
	c.color = sf::Color::Red;

	triangle.setPrimitiveType(sf::Triangles);

	triangle.append(a);
	triangle.append(b);
	triangle.append(c);

	resources.insert(std::pair<std::string, sf::VertexArray>("triangle", triangle));
}

void ResourceManager::DefineQuad()
{
	quad.setPrimitiveType(sf::Quads);

	sf::Vertex a; a.position = sf::Vector2f(0, 0);
	sf::Vertex b; b.position = sf::Vector2f(50, 0);
	sf::Vertex c; c.position = sf::Vector2f(50, 50);

	sf::Vertex d; d.position = sf::Vector2f(0, 50);

	quad.append(a); quad.append(b); quad.append(c); quad.append(d);

	resources.insert(std::pair<std::string, sf::VertexArray>("quad", quad));

}

void ResourceManager::DefinePentagon()
{
	//pentagon.setPrimitiveType(sf::Triangles);
}

void ResourceManager::DefinePrzemekShape()
{
	przemek.setPrimitiveType(sf::Triangles);

	sf::Vertex a; a.position = sf::Vector2f(0, 0); a.color = sf::Color::Red;
	sf::Vertex b; b.position = sf::Vector2f(50, 0); b.color = sf::Color::Red;
	sf::Vertex c; c.position = sf::Vector2f(0, 50); c.color = sf::Color::Red;

	sf::Vertex d; d.position = sf::Vector2f(50, 0);
	sf::Vertex e; e.position = sf::Vector2f(100, 0);
	sf::Vertex f; f.position = sf::Vector2f(50, 50);

	sf::Vertex g; g.position = sf::Vector2f(0, 50);
	sf::Vertex h; h.position = sf::Vector2f(50, 0);
	sf::Vertex i; i.position = sf::Vector2f(50, 50);

	sf::Vertex j; j.position = sf::Vector2f(50, -50);
	sf::Vertex k; k.position = sf::Vector2f(100, -50);
	sf::Vertex l; l.position = sf::Vector2f(100, 0);

	sf::Vertex m; m.position = sf::Vector2f(50, 0);
	sf::Vertex n; n.position = sf::Vector2f(50, -50);
	sf::Vertex o; o.position = sf::Vector2f(100, 0);
	
	// Break off point for weird gjk
	sf::Vertex p; p.position = sf::Vector2f(0, 0);
	sf::Vertex q; q.position = sf::Vector2f(50, -50);
	sf::Vertex r; r.position = sf::Vector2f(50, 0);

	sf::Vertex s; s.position = sf::Vector2f(0, 0);
	sf::Vertex t; t.position = sf::Vector2f(0, -50);
	sf::Vertex u; u.position = sf::Vector2f(50, -50);

	// Another one
	sf::Vertex v; v.position = sf::Vector2f(0, 0);
	sf::Vertex w; w.position = sf::Vector2f(-50, -50);
	sf::Vertex x; x.position = sf::Vector2f(0, -50);

	sf::Vertex a2; a2.position = sf::Vector2f(0, 0);
	sf::Vertex b2; b2.position = sf::Vector2f(-50, -50);
	sf::Vertex c2; c2.position = sf::Vector2f(-50, 0);

	sf::Vertex d2; d2.position = sf::Vector2f(0, 0);
	sf::Vertex e2; e2.position = sf::Vector2f(-50, 0);
	sf::Vertex f2; f2.position = sf::Vector2f(-50, 50);

	sf::Vertex g2; g2.position = sf::Vector2f(0, 0);
	sf::Vertex h2; h2.position = sf::Vector2f(0, 50);
	sf::Vertex i2; i2.position = sf::Vector2f(-50, 50);

	sf::Vertex j2; j2.position = sf::Vector2f(0, 50);
	sf::Vertex k2; k2.position = sf::Vector2f(50, 50);
	sf::Vertex l2; l2.position = sf::Vector2f(0, 100);

	sf::Vertex m2; m2.position = sf::Vector2f(0, 50);
	sf::Vertex n2; n2.position = sf::Vector2f(-50, 50);
	sf::Vertex o2; o2.position = sf::Vector2f(0, 100);


	przemek.append(a); przemek.append(b); przemek.append(c); przemek.append(d); przemek.append(e); przemek.append(f); przemek.append(g); przemek.append(h); przemek.append(i);
	przemek.append(j); przemek.append(k); przemek.append(l);
	przemek.append(m); przemek.append(n); przemek.append(o);
	przemek.append(p); przemek.append(q); przemek.append(r);
	przemek.append(s); przemek.append(t); przemek.append(u);
	przemek.append(v); przemek.append(w); przemek.append(x);
	przemek.append(a2); przemek.append(b2); przemek.append(c2);
	przemek.append(d2); przemek.append(e2); przemek.append(f2);
	przemek.append(g2); przemek.append(h2); przemek.append(i2);
	przemek.append(j2); przemek.append(k2); przemek.append(l2);
	przemek.append(m2); przemek.append(n2); przemek.append(o2);

	resources.insert(std::pair<std::string, sf::VertexArray>("przemek", przemek));
}

/*void ResourceManager::DefinePentagon()
{

}*/

std::vector<sf::Vector2f> ResourceManager::GetPoints(std::string name)  //Return source points
{
	std::vector<sf::Vector2f> points;
	std::map<std::string, sf::VertexArray>::iterator results = resources.find(name);

	for (int i = 0; i < (results->second.getVertexCount()); i++)
	{
		points.push_back(results->second[i].position);
	}

	return points;
}

sf::VertexArray* ResourceManager::Get(std::string name)
{
	std::map<std::string, sf::VertexArray>::iterator results = resources.find(name);
	if (results == resources.end())  //If the object does not exist then return a null pointer
		return nullptr;

	return &(results->second);

}