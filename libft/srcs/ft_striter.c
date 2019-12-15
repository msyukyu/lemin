/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striter.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pvanderl <pvanderl@students.s19.be>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/10/04 19:29:53 by pvanderl		  #+#	#+#			 */
/*   Updated: 2018/10/18 16:25:05 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	int i;

	i = 0;
	if (s && f && *f)
		while (*(s + i))
			f(s + i++);
}
