

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

CREATE TABLE IF NOT EXISTS `doc_index` (
  `docid` bigint(20) NOT NULL default '0',
  `token` varchar(200) character set utf8 collate utf8_unicode_ci NOT NULL,
  `pos` bigint(20) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `index_table` (
  `id` bigint(20) NOT NULL default '0',
  `parentid` bigint(20) NOT NULL default '0',
  `name` varchar(200) collate utf8_unicode_ci NOT NULL,
  `extName` varchar(200) collate utf8_unicode_ci default NULL,
  `path` varchar(200) collate utf8_unicode_ci NOT NULL,
  `size` int(20) NOT NULL,
  `date` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `desc` varchar(200) collate utf8_unicode_ci default NULL,
  `selected_times` int(5) default '0',
  `is_folder` tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `name` (`name`,`path`,`desc`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
