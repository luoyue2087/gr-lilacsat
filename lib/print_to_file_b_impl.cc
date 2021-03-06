/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "print_to_file_b_impl.h"

namespace gr {
  namespace lilacsat {

    print_to_file_b::sptr
    print_to_file_b::make(const std::string& path, int16_t format)
    {
      return gnuradio::get_initial_sptr
        (new print_to_file_b_impl(path, format));
    }

    /*
     * The private constructor
     */
    print_to_file_b_impl::print_to_file_b_impl(const std::string& path, int16_t format)
      : gr::sync_block("print_to_file_b",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(0, 0, 0))
    {
	fp = fopen(path.data(), "rw+");
    }

    /*
     * Our virtual destructor.
     */
    print_to_file_b_impl::~print_to_file_b_impl()
    {
	fclose(fp);
    }

    int
    print_to_file_b_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
	int i;

        // Do <+signal processing+>
	for(i=0; i<noutput_items; i++)
	{
		fprintf(fp, "%02x ", in[i] & 0xff);
	}
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace lilacsat */
} /* namespace gr */

