//
//  vector.cpp
//  BarnesGalaxySimulation
//
//  Created by Noé on 02/07/2021.
//  Copyright © 2021 Noé. All rights reserved.
//

#include "vector.hpp"

// Construit un vecteur

Vector::Vector()
{
    x = 0.;
    y = 0.;
}

// Construit un vecteur à partir d'un autre vecteur

Vector::Vector(const Vector& vector)
{
    *this = vector;
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector::Vector(const Float& x, const Float& y)
{
    this->x = x;
    this->y = y;
}

// Assignations

void Vector::operator=(const Vector& vector)
{
    x = vector.x;
    y = vector.y;
}

void Vector::operator+=(const Vector& vector)
{
    *this = *this + vector;
}

void Vector::operator-=(const Vector& vector)
{
    *this = *this - vector;
}

void Vector::operator*=(const Float& number)
{
    *this = *this * number;
}

void Vector::operator/=(const Float& number)
{
    *this = *this / number;
}

// Donne la norme du vecteur

Float Vector::get_norm() const
{
    return sqrt(x * x + y * y);
}

// Donne la norme du vecteur au carré

Float Vector::get_norm_2() const
{
    return x * x + y * y;
}

// Modifie la norme du vecteur

void Vector::set_norm(const Float& norm)
{
    *this = normalized(*this) * norm;
}

// Normalise le vecteur

void Vector::normalize()
{
    if (get_norm() != 0.)
        *this /= get_norm();
}

// Met toutes les composantes à zéro

void Vector::clear()
{
    *this = Vector();
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector Vector_cartesian(const Float& x, const Float& y)
{
    return Vector(x, y);
}

// Addition

Vector operator+(const Vector& vector_1, const Vector& vector_2)
{
    return Vector(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
}

// Soustraction

Vector operator-(const Vector& vector_1, const Vector& vector_2)
{
    return Vector(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
}

// Inversion

Vector operator-(const Vector& vector)
{
    return Vector(0., 0.) - vector;
}

// Produits

Vector operator*(const Vector& vector, const Float& number)
{
    return Vector(vector.x * number, vector.y * number);
}

Vector operator*(const Float& number, const Vector& vector)
{
    return Vector(number * vector.x, number * vector.y);
}

// Produit scalaire

Float operator*(const Vector& vector_1, const Vector& vector_2)
{
    return vector_1.x * vector_2.x + vector_1.y * vector_2.y ;
}


// Division

Vector operator/(const Vector& vector, const Float& number)
{
    if (number == 0.)
        throw std::invalid_argument("division by 0");
    
    return Vector(vector.x / number, vector.y / number);
}

// Egalités

bool operator==(const Vector& vector_1, const Vector& vector_2)
{
    return (vector_1.x == vector_2.x && vector_1.y == vector_2.y);
}

bool operator!=(const Vector& vector_1, const Vector& vector_2)
{
    return (!(vector_1 == vector_2));
}

// Affichage

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}

// Donne la distance entre deux points

Float get_distance(const Vector& point_1, const Vector& point_2)
{
    return (point_2 - point_1).get_norm();
}

// Donne la distance entre deux points au carré

Float get_distance_2(const Vector& point_1, const Vector& point_2)
{
    return (point_2 - point_1).get_norm_2();
}


// Donne le vecteur normalisé

Vector normalized(const Vector& vector)
{
    if (vector.get_norm() != 0.)
        return vector / vector.get_norm();
}
