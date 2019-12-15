/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_tolower.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pvanderl <pvanderl@students.s19.be>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/10/04 19:32:34 by pvanderl		  #+#	#+#			 */
/*   Updated: 2018/10/12 09:56:27 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

int		ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (c + 32);
	return (c);
}
