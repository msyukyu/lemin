/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striteri.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pvanderl <pvanderl@students.s19.be>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/10/04 19:30:02 by pvanderl		  #+#	#+#			 */
/*   Updated: 2018/10/18 16:25:24 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = -1;
	if (s && f && *f)
		while (*(s + ++i))
			f(i, s + i);
}
