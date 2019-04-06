/* 
 *  Copyright (C) 2009-2011 milkyjing <milkyjing@gmail.com>
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "../file.h"
#include "../pix.h"
#include "../text.h"
#include "../image.h"
#include "../utility.h"

const char *tcaxlib_get_version()
{
    return TCAXLIB_VER_STR;
}

/* overloads */
/* file */
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(file_reset_overloads, reset, 1, 2)

/* image */
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ImagePix_overloads, get_pix_from_image, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(SavePix_overloads,  save_pix_to_image,  2, 4)

BOOST_PYTHON_MODULE(tcaxLib)
{
    /*      python_function_name cpp_function_name                                 actual_python_function */
    py::def("tcaxLibGetVersion", tcaxlib_get_version);                             //tcaxLibGetVersion()
    
    /* in pix.h */
    py::class_<pix>("Pix")
    .def("PixPoints",            &pix::pix_points)                                 //PixPoints(PIX)
    .def("BlankPix",             &pix::create_blank_pix)                           //BlankPix(width, height, rgba)
    .def("PixResize",            &pix::resample_py_pix)                            //PixResize(PIX, width, height)
    .def("PixResizeF",           &pix::resample_py_pix_ex)                         //PixResizeF(PIX, width, height)
    .def("PixTexture",           &pix::apply_pix_texture)                          //PixTexture(PIX, texture)
    .def("PixMask",              &pix::apply_pix_mask)                             //PixMask(PIX, mask)
    .def("PixReplaceAlpha",      &pix::pix_replace_alpha)                          //PixReplaceAlpha(PIX, PIX_alpha)
    .def("PixEnlarge",           &pix::enlarge_py_pix)                             //PixEnlarge(PIX, x, y)
    .def("PixCrop",              &pix::crop_py_pix)                                //PixCrop(PIX, left, top, right, bottom)
    .def("PixStrip",             &pix::py_pix_strip_blank)                         //PixStrip(PIX)
    .def("PixBlur",              &pix::apply_gauss_blur)                           //PixBlur(PIX, radius)
    .def("CombinePixs",          &pix::combine_two_pixs)                           //CombinePixs(back, overlay)
    .def("PixColorMul",          &pix::pix_color_multiply)                         //PixColorMul(PIX, r_f, g_f, b_f, a_f)
    .def("PixColorShift",        &pix::pix_color_shift)                            //PixColorShift(PIX, r, g, b, a)
    .def("PixColorTrans",        &pix::pix_color_transparent)                      //PixColorTrans(PIX, rgb)
    .def("PixColorRGBA",         &pix::pix_color_flat_rgba)                        //PixColorRGBA(PIX, rgba)
    .def("PixColorRGB",          &pix::pix_color_flat_rgb)                         //PixColorRGB(PIX, rgb)
    .def("PixColorA",            &pix::pix_color_flat_alpha)                       //PixColorA(PIX, alpha)
    .def("BilinearFilter",       &pix::bilinear_filter)                            //BilinearFilter(PIX, offset_x, offset_y)
    .def("ScaleFilter",          &pix::scale_filter)                               //ScaleFilter(PIX, offset_x, offset_y)
    .def("InitBigPix",           &pix::init_big_pix)                               //InitBigPix()
    .def("BigPixAdd",            &pix::big_pix_add)                                //BigPixAdd(BIG_PIX, PIX, offset_x, offset_y, layer)
    .def("ConvertBigPix",        &pix::convert_big_pix)                            //ConvertBigPix(BIG_PIX)
    ;

    /* in file.h */
    py::class_<file>("File", py::init<const char *, py::optional<const char *>>()) //file(ass_file, ass_header)
    .def("WriteAssFile",         &file::write_ass_file)                            //WriteAssFile(ASS_BUF)
    .def("reset",                &file::reset, file_reset_overloads())             //reset(ass_file, ass_header)
    .def("isSuccess",            &file::is_success)                                //isSuccess()
    .def("isAppend",             &file::is_append)                                 //isAppend()
    ;

    /* in text.h */
    py::class_<text>("Text", py::init<const char *,
                                      int,
                                      int,
                                      int,
                                      double,
                                      uint32_t,
                                      int,
                                      int>())                                       //text(font_file, face_id, font_size, spacing, space_scale, color, bord, is_outline)
    .def("TextPix",              &text::get_pix_from_text)                          //TextPix(pyFont, texts)
    .def("TextPix",              &text::get_pix_from_text_2)                        //TextPix(font_file, face_id, font_size, spacing, space_scale, color, bord, is_outline, texts)
    .def("TextOutlinePoints",    &text::get_text_outline_as_points)                 //TextOutlinePoints(pyFont, text, density)
    .def("TextOutlinePoints",    &text::get_text_outline_as_points_2)               //TextOutlinePoints(font_file, face_id, font_size, text, density)
    .def("TextMetrics",          &text::get_text_metrics_2)                         //TextMetrics(pyFont, text)
    .def("TextMetrics",          &text::get_text_metrics)                           //TextMetrics(font_file, face_id, font_size, spacing, space_scale, text)
    .def("isSuccess",            &text::is_success)                                 //isSuccess()
    ;

    /* in image.h */
    py::class_<image>("Image") //image()
    .def("ImagePix",             &image::get_pix_from_image, ImagePix_overloads())  //ImagePix(filename, width = 0, height = 0)
    .def("SavePix",              &image::save_pix_to_image, SavePix_overloads())    //SavePix(filename, PIX, width = 0, height = 0)
    ;

    /* in utility.h */
    py::class_<utility>("Utility")
    .def("TextOutlineDraw",      &utility::get_text_outline_as_string)               //TextOutlineDraw(pyFont, text, x, y)
    .def("TextOutlineDraw",      &utility::get_text_outline_as_string_2)             //TextOutlineDraw(font_file, face_id, font_size, text, x, y)
    .def("IsCjk",                &utility::is_c_or_j_or_k)                           //IsCjk(text)
    .def("VertLayout",           &utility::vertical_layout_ass)                      //VertLayout(text)
    .def("ShowProgress",         &utility::show_progress)                            //ShowProgress(total, completed, file_id, file_num)
    .def("Bezier1",              &utility::bezier_curve_linear)                      //Bezier1(nPoints, xs, ys, xe, ye)
    .def("Bezier2",              &utility::bezier_curve_quadratic)                   //Bezier2(nPoints, xs, ys, xe, ye, xc, yc)
    .def("Bezier3",              &utility::bezier_curve_cubic)                       //Bezier3(nPoints, xs, ys, xe, ye, xc1, yc1, xc2, yc2)
    .def("BezierN",              &utility::bezier_curve_random)                      //BezierN(nPoints, xs, ys, xe, ye, xl1, yl1, xl2, yl2, order)
    .def("GetFontSize",          &utility::get_actual_font_size)                     //GetFontSize(font_file, face_id, font_size)
    .def("CairoFontSize",        &utility::calc_cairo_font_size)                     //CairoFontSize(font_file, face_id, font_size)
    ;
}
