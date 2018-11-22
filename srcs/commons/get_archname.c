/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_archname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:11:10 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/22 08:50:17 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

char    *get_archname(cpu_type_t cputype)
{
    if (cputype == CPU_TYPE_MC680x0)
        return ("CPU_TYPE_MC680x0");
    if (cputype == CPU_TYPE_X86)
        return ("CPU_TYPE_X86");
    if (cputype == CPU_TYPE_I386)
        return ("CPU_TYPE_I386");
    if (cputype == CPU_TYPE_X86_64)
        return ("CPU_TYPE_X86_64");
    if (cputype == CPU_TYPE_MC98000)
        return ("CPU_TYPE_MC98000");
    if (cputype == CPU_TYPE_HPPA)
        return ("CPU_TYPE_HPPA");
    if (cputype == CPU_TYPE_ARM)
        return ("CPU_TYPE_ARM");
    if (cputype == CPU_TYPE_ARM64)
        return ("CPU_TYPE_ARM64");
    if (cputype == CPU_TYPE_MC88000)
        return ("CPU_TYPE_MC88000");
    if (cputype == CPU_TYPE_SPARC)
        return ("CPU_TYPE_SPARC");
    if (cputype == CPU_TYPE_I860)
        return ("CPU_TYPE_I860");
    if (cputype == CPU_TYPE_POWERPC)
        return ("CPU_TYPE_POWERPC");
    if (cputype == CPU_TYPE_POWERPC64)
        return ("CPU_TYPE_POWERPC64");
    if (cputype == CPU_TYPE_I386)
        return ("CPU_TYPE_I386");
    if (cputype == CPU_TYPE_POWERPC)
        return ("CPU_TYPE_POWERPC");
    if (cputype == CPU_TYPE_X86_64)
        return ("CPU_TYPE_X86_64");
    return ("");
}