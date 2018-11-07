<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">

<html>
	<head>
		<title>BSA - List of Scouts</title>
		<link rel="stylesheet" type="text/css" href="bsa.css"/>
	</head>

	<body>
			<div id="content">
			<p id="home" style="text-align:center">Back to home? <a href="../index.html">Click Here</a></p>
			<hr />

			<div id="top">
				<img id="bsa_logo" src="bsa.jpg"/>
				<h1 id="title">BSA</h1>
				<h2 id="sub_title">List of Scouts</h2>
			</div>
			<div id="stuff">
			<p>Example: Name, Council, Troop</p>
			<table class="larger_table">

				<!--Here is where the loop starts-->
				<xsl:for-each select="/bsa/council/troop/scout">
				<tr>
					<td>
						<button type="button">
							<xsl:attribute name="onclick">
								toggleRow(<xsl:value-of select="position()"/>);
							</xsl:attribute>
							Show
						</button>
					</td>
					<td>
						<xsl:value-of select="first_name"/>&#160;
						<xsl:value-of select="last_name"/>&#160;-
						<xsl:value-of select="../../@name"/>&#160;-
						<xsl:value-of select="../@number"/>&#160;|
						<xsl:value-of select="../@name"/>
					</td>
				</tr>
				<tr style="visibility: collapse;">
					<xsl:attribute name="id">
						<xsl:value-of select="position()"/>
					</xsl:attribute>
					<td/>
					<td>
					<table class="tiny_table">
						<tr>
							<td>Contact Info:</td>
						</tr>
						<tr>
							<td>&#160;&#160;&#160;&#160;Phone:</td>
							<td><xsl:value-of select="phone"/></td>
						</tr>
						<tr>
							<td>&#160;&#160;&#160;&#160;Address:</td>
							<td><xsl:value-of select="address/street"/></td>
						</tr>
						<tr>
							<td></td>
							<td><xsl:value-of select="address/city"/>,&#160;<xsl:value-of select="address/state"/></td>
						</tr>
						<tr>
							<td>&#160;&#160;&#160;&#160;Ranks:</td>
							<td>
								<xsl:for-each select="rank">
									<xsl:value-of select="text()"/>&#160;
									(<xsl:value-of select="@date_earned"/>)&#160;
								</xsl:for-each>
							</td>
						</tr>
						<tr>
							<td>&#160;&#160;&#160;&#160;Badges:</td>
							<td>
								<xsl:for-each select="merit_badge">
									<xsl:value-of select="text()"/>&#160;
									(<xsl:value-of select="@date_earned"/>)&#160;
								</xsl:for-each>
							</td>
						</tr>
					</table>
				</td>
				</tr>

				</xsl:for-each>
			</table>
			</div>
		</div>
		<script src="bsa.js"></script>

	</body>
</html>


</xsl:template>
</xsl:stylesheet>
<!--
      <xsl:for-each select="catalog/cd">
        <tr>
          <td><xsl:value-of select="title"/></td>
          <td><xsl:value-of select="artist"/></td>
        </tr>
      </xsl:for-each> -->
