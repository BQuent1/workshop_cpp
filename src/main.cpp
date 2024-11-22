#include <sil/sil.hpp>
#include <iostream>
#include <string>
#include <numbers>
#include <cmath>
#include "random.hpp"
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <vector>

#include <cerrno>
#include <cfenv>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }

    image.save("output/output_off/volf_vert.png");
}

void swap_canaux(sil::Image &img)
{
    for (glm::vec3 &color : img.pixels())
    {
        int temp = color.r;
        color.b = color.r;
        color.r = temp;
    }
    img.save("output/output_off/volf_swap.png");
}

void negatif(sil::Image &img)
{
    for (glm::vec3 &color : img.pixels())
    {
        color = 1.f - color;
    }

    img.save("output/output_off/volf_negatif.png");
}

void noir_blanc(sil::Image &img)
{
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            float gray = img.pixel(x, y).r * 0.2126f + img.pixel(x, y).g * 0.7152f + img.pixel(x, y).b * 0.0722f;
            img.pixel(x, y).r = img.pixel(x, y).g = img.pixel(x, y).b = gray;
        }
    }

    img.save("output/output_off/volf_noir_et_blanc.png");
}

void degrade()
{
    sil::Image image{300 /*width*/, 200 /*height*/};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float valeur = static_cast<float>(x) / static_cast<float>(image.width() - 1);

            image.pixel(x, y).r = image.pixel(x, y).g = image.pixel(x, y).b = valeur;
        }
    }

    image.save("output/output_off/degrade.png");
}

void symetrie_axial_verticale(sil::Image &img)
{
    for (int x{0}; x < img.width(); x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x, y).r = img.pixel(img.width() - (x + 1), y).r;
            img.pixel(x, y).b = img.pixel(img.width() - (x + 1), y).b;
            img.pixel(x, y).g = img.pixel(img.width() - (x + 1), y).g;
        }
    }

    img.save("output/output_off/volf_symetrie_verticale.png");
}

void symetrie_axial_horizontale(sil::Image &img)
{
    for (int x{0}; x < img.width(); x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x, y).r = img.pixel(x, img.height() - (y + 1)).r;
            img.pixel(x, y).b = img.pixel(x, img.height() - (y + 1)).b;
            img.pixel(x, y).g = img.pixel(x, img.height() - (y + 1)).g;
        }
    }

    img.save("output/output_off/volf_symetrie_horizontale.png");
}

void miroir(sil::Image &img)
{
    sil::Image newImg = img;
    for (int x{0}; x < img.width(); x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x, y).r = newImg.pixel(img.width() - (x + 1), y).r;
            img.pixel(x, y).b = newImg.pixel(img.width() - (x + 1), y).b;
            img.pixel(x, y).g = newImg.pixel(img.width() - (x + 1), y).g;
        }
    }

    img.save("output/output_off/volf_miroir.png");
}

void rotation90(sil::Image &image)
{
    sil::Image newImg{image.height(), image.width()};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int newX = image.height() - 1 - y;
            int newY = x;

            newImg.pixel(newX, newY).r = image.pixel(x, y).r;
            newImg.pixel(newX, newY).g = image.pixel(x, y).g;
            newImg.pixel(newX, newY).b = image.pixel(x, y).b;
        }
    }

    newImg.save("output/output_off/volf_tourne_la_tete.png");
}

void rgbsplit(sil::Image image)
{
    sil::Image newImg{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            newImg.pixel(x, y).g = image.pixel(x, y).g;
            if (x >= 20)
            {
                newImg.pixel(x, y).b = image.pixel(x - 18, y).b;
            }
            if (x <= image.width() - 20)
            {
                newImg.pixel(x, y).r = image.pixel(x + 18, y).r;
            }
        }
    }
    newImg.save("output/output_off/volf_plein_de_couleurs.png");
}

void luminosite(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 1.2f);
            image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 1.2f);
            image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 1.2f);
        }
    }

    image.save("output/output_off/volf_plus_fonce.png");
}

void disque(int rayon, int xcentre, int ycentre, int num)
{
    sil::Image image{500 /*width*/, 500 /*height*/};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if (std::pow(x - xcentre, 2) + std::pow(y - ycentre, 2) <= std::pow(rayon, 2))
            {
                image.pixel(x, y).r = image.pixel(x, y).b = image.pixel(x, y).g = 0.2f;
            }
        }
    }
    std::string chemin = "output/cercles/pouet" + std::to_string(num) + ".png";
    image.save(chemin);
}

void cercle(int thickness)
{
    sil::Image image{500 /*width*/, 500 /*height*/};
    int rayon = 125;
    int xcentre = image.width() / 2;
    int ycentre = image.height() / 2;
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            if (std::pow(x - xcentre, 2) + std::pow(y - ycentre, 2) <= std::pow(rayon, 2) and std::pow(x - xcentre, 2) + std::pow(y - ycentre, 2) >= std::pow(rayon - thickness, 2))
            {
                image.pixel(x, y).r = 0.8f;
                image.pixel(x, y).b = image.pixel(x, y).g = 0.2f;
            }
        }
    }
    image.save("output/output_off/juste_un_cercle.png");
}

void cercle_rosace(int thickness, sil::Image &img, int rayon, int xcentre, int ycentre)
{
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            if (std::pow(x - xcentre, 2) + std::pow(y - ycentre, 2) <= std::pow(rayon, 2) and std::pow(x - xcentre, 2) + std::pow(y - ycentre, 2) >= std::pow(rayon - thickness, 2))
            {
                // std::cout << "here\n";
                img.pixel(x, y).r = 0.8f;
                img.pixel(x, y).b = img.pixel(x, y).g = 0.2f;
            }
        }
    }
}

void rosace(int thickness, int rayon)
{
    // x = rcos teta
    // y = rsin teta
    // avec r le rayon du cercle
    // un cercle centre, un a 0, un a pi3, un a 2pi/3, un a 3pi/4,...

    constexpr double pi = 3.14159265358979323846;

    sil::Image image{500, 500};
    cercle_rosace(thickness, image, rayon, image.width() / 2, image.height() / 2);
    for (int i = 0; i < 6; i++)
    {
        cercle_rosace(thickness, image, rayon, image.width() / 2 + rayon * std::cos(i * pi / 3), image.width() / 2 + rayon * std::sin(i * pi / 3));
    }
    image.save("output/output_off/belle_rosace.png");
}

void mosaique(sil::Image &img, int nb_image)
{
    sil::Image newImg{nb_image * img.width(), nb_image * img.height()};

    // Parcourir chaque "bloc" de la mosaïque
    for (int i = 0; i < nb_image; ++i)
    { // Parcourir les colonnes de mosaïque
        for (int j = 0; j < nb_image; ++j)
        { // Parcourir les lignes de mosaïque
            for (int xi = 0; xi < img.width(); ++xi)
            {
                for (int yi = 0; yi < img.height(); ++yi)
                {
                    int targetX = i * img.width() + xi;
                    int targetY = j * img.height() + yi;

                    newImg.pixel(targetX, targetY) = img.pixel(xi, yi);
                }
            }
        }
    }

    newImg.save("output/output_off/volf_plein_de_fois.png");
}

void mosaique_miroir(sil::Image &img, int nb_image)
{
    sil::Image newImg{nb_image * img.width(), nb_image * img.height()};

    // Parcourir chaque "bloc" de la mosaïque
    for (int i = 0; i < nb_image; ++i)
    {
        for (int j = 0; j < nb_image; ++j)
        {

            for (int xi = 0; xi < img.width(); ++xi)
            {
                for (int yi = 0; yi < img.height(); ++yi)
                {
                    int sourceX = xi;
                    int sourceY = yi;

                    if (i % 2 == 1)
                    { // Miroir horizontal pour colonnes impaires
                        sourceX = img.width() - 1 - xi;
                    }
                    if (j % 2 == 1)
                    { // Miroir vertical pour lignes impaires
                        sourceY = img.height() - 1 - yi;
                    }

                    // Calculer les indices cibles dans la mosaïque
                    int targetX = i * img.width() + xi;
                    int targetY = j * img.height() + yi;

                    newImg.pixel(targetX, targetY) = img.pixel(sourceX, sourceY);
                }
            }
        }
    }

    newImg.save("output/output_off/volf_plein_de_fois_mais_de_maniere_rigolote.png");
}

void glitch(sil::Image &img)
{
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            if (true_with_probability(0.0003f))
            {
                int longueur_rec = random_int(10, 40);
                int largeur_rec = random_int(3, 10);

                longueur_rec = std::min(longueur_rec, img.width() - x);
                largeur_rec = std::min(largeur_rec, img.height() - y);

                sil::Image img_temp{longueur_rec, largeur_rec};
                for (int i = 0; i < longueur_rec; i++)
                {
                    for (int j = 0; j < largeur_rec; j++)
                    {
                        img_temp.pixel(i, j) = img.pixel(x + i, y + j);
                    }
                }

                int posx_alea = random_int(0, img.width() - longueur_rec);
                int posy_alea = random_int(0, img.height() - largeur_rec);

                for (int ii = 0; ii < longueur_rec; ii++)
                {
                    for (int jj = 0; jj < largeur_rec; jj++)
                    {
                        img.pixel(x + ii, y + jj) = img.pixel(posx_alea + ii, posy_alea + jj);
                        img.pixel(posx_alea + ii, posy_alea + jj) = img_temp.pixel(ii, jj);
                    }
                }
            }
        }
    }

    img.save("output/output_off/volf_ca_gresille.png");
}

void mandelbrot()
{
    sil::Image image{500 /*width*/, 500 /*height*/};
    // 1/125x-2
    int iteration{50};
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int i{0};
            std::complex<float> z_init{0.f, 0.f};
            float real = (float(x) / image.width()) * (1.f - (-2.f)) + (-2.f);
            float imag = (float(y) / image.height()) * (1.f - (-1.f)) + (-1.f);
            std::complex<float> c{real, imag};

            while (i < iteration and std::abs(z_init) < 2)
            {
                z_init = z_init * z_init + c;
                i++;
                // std::cout << z_init << "\n";
            }

            if (std::abs(z_init) < 2 or i < iteration)
            {
                image.pixel(x, y).r = image.pixel(x, y).g = image.pixel(x, y).b = (float)i / iteration;
            }
            else
            {
                image.pixel(x, y).r = image.pixel(x, y).g = image.pixel(x, y).b = 0.f;
            }
        }
    }
    image.save("output/output_off/pain_d_amande.png");
}

void tramage(sil::Image img, float bayer_r, int i)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {-0.5, 0, -0.375, 0.125},
        {0.25, -0.25, 0.375, -0.125},
        {-0.3125, 0.1875, -0.4375, 0.0625},
        {0.4375, -0.0625, 0.3125, -0.1875},
    };
    // float bayer_r = 0.9f; // Valeur maximale pour le Bayer

    for (int sy = 0; sy < img.height(); sy++)
    {
        for (int sx = 0; sx < img.width(); sx++)
        {
            float orig_color = img.pixel(sx, sy).r;
            float bayer_value = bayer_matrix_4x4[sy % bayer_n][sx % bayer_n];
            float output_color = orig_color + (bayer_r * bayer_value);

            float color_result = 0.f;
            if (output_color >= (bayer_r / 2))
            {
                color_result = 1.f;
            }

            img.pixel(sx, sy).r = img.pixel(sx, sy).g = img.pixel(sx, sy).b = color_result;
        }
    }

    img.save("output/tramages/tramage" + std::to_string(i) + ".png");
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image &img)
{
    constexpr double pi = 3.14159265358979323846;

    glm::vec2 centre(img.width() / 2.0, img.height() / 2.0); // Centre de l'image

    sil::Image source = img;

    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            glm::vec2 point(x, y);
            int distance{glm::distance(centre, point)};
            float angle = 0.006 * distance;

            glm::vec2 rotatedPoint = rotated(point, centre, angle);
            // std::cout << rotatedPoint.x << rotatedPoint.y << " , \n";

            int rx = static_cast<int>(std::round(rotatedPoint.x));
            int ry = static_cast<int>(std::round(rotatedPoint.y));
            if (rx >= 0 && rx < img.width() && ry >= 0 && ry < img.height())
            {
                img.pixel(x, y) = source.pixel(rx, ry);
            }
            else
            {
                img.pixel(x, y).r = img.pixel(x, y).g = img.pixel(x, y).b = 0.f; // Noir
            }
        }
    }

    img.save("output/output_off/volf_bourre.png");
}

float clamp(float value, float min, float max)
{
    return std::max(min, std::min(value, max));
}

void convolution(sil::Image &img, const std::vector<std::vector<float>> &kernel)
{
    sil::Image result = img;

    int kernel_size = kernel.size();
    std::cout << kernel_size;
    int offset = kernel_size / 2; // Déplacement pour correspondre au centre du noyau

    for (int x = offset; x < img.width() - offset; x++)
    {
        for (int y = offset; y < img.height() - offset; y++)
        {
            float const_r = 0.f;
            float const_g = 0.f;
            float const_b = 0.f;

            for (int i = -offset; i <= offset; i++)
            {
                for (int j = -offset; j <= offset; j++)
                {
                    float poid = kernel[i + offset][j + offset];

                    const_r += poid * img.pixel(x + i, y + j).r;
                    const_g += poid * img.pixel(x + i, y + j).g;
                    const_b += poid * img.pixel(x + i, y + j).b;
                }
            }

            result.pixel(x, y).r = clamp(const_r, 0.f, 255.f); // Clamp pour éviter les débordements
            result.pixel(x, y).g = clamp(const_g, 0.f, 255.f);
            result.pixel(x, y).b = clamp(const_b, 0.f, 255.f);
        }
    }

    result.save("output/output_off/volf_gravure_sur_pierre.png");
}

std::vector<std::vector<float>> blur_vec = {{0.0625f, 0.125f, 0.0625f}, {0.125f, 0.25f, 0.125f}, {0.0625f, 0.125f, 0.0625f}};
std::vector<std::vector<float>> outline_vec = {{-1.f, -1.f, -1.f}, {-1.f, 8, -1.f}, {-1.f, -1.f, -1.f}};
std::vector<std::vector<float>> emboss_vec = {{-2.f, -1.f, 0.f}, {-1.f, 1.f, 1.f}, {0.f, 1.f, 2.f}};

int main()
{
    sil::Image volf_img{"images/volf_officiel.png"};
    convolution(volf_img,emboss_vec);
    return 0;
}
