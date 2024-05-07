-- MySQL dump 10.13  Distrib 8.0.35, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: home_decoration
-- ------------------------------------------------------
-- Server version	8.0.35

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工编号''',
  `account_number` varchar(15) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''账号''',
  `password` varchar(15) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''密码''',
  `identity` enum('业务员','设计师总监','设计师','项目总经理','项目经理','财务','管理员') CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '''身份''',
  PRIMARY KEY (`account_number`),
  KEY `account_employee_id_fk` (`id`),
  CONSTRAINT `account_employee_id_fk` FOREIGN KEY (`id`) REFERENCES `employee` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES ('admin0000','admin','123456','管理员'),('17149815797243132198325','chenqi30','chenqi123','项目经理'),('17149836666324052788171','hanjiu31','hanjiu123','业务员'),('17149741681092521189659','lisi35','lisi123','业务员'),('17149837912752705328407','liujiumei32','liujiumei123','项目经理'),('17149746562851103169968','liuxiaohong25','liuxiaohong123','设计师'),('17149742095481024838461','wangxiaohua22','wangxiaohua123','设计师'),('17149831610353676096239','wuba33','wuba123','项目经理'),('17149826590672879562946','yangxiaoli27','yangxiaoli123','设计师总监'),('17149837188451120575386','youxiaoming26','123456','业务员'),('1714974123172173345502','zhangsan28','zhangsan123','业务员'),('17149743247571910234800','zhaoliu40','zhaoliu123','项目总经理'),('17149981322701211190081','zhengxiaolan26','123456','业务员'),('1714982624349520807794','zhouxiaoming23','zhouxiaoming123','财务'),('1714983250926899865052','zhuxiaojuan29','zhuxiaojuan123','设计师');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  `name` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '''客户姓名''',
  `age` int NOT NULL COMMENT '''客户年龄''',
  `gender` enum('男','女') CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '''客户性别''',
  `phone` varchar(15) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''客户电话''',
  `proj_id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `customer_project_id_fk` (`proj_id`),
  CONSTRAINT `customer_project_id_fk` FOREIGN KEY (`proj_id`) REFERENCES `project` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES ('17149954671521524493009','张三',36,'男','13812345678','1714995467136650466941'),('1714995535788831322536','李四',40,'女','13998765432','17149955357763586832654'),('17149955841901214253997','王五',28,'男','13611112222','17149955841884013675413'),('17149956234083515763119','赵六',45,'女','13544443333','17149956234051635358594'),('17149956508221001180006','小明',32,'男','13755556666','17149956508091717477684'),('17149957120584077450257','小红',30,'女','13866667777','17149957120552262177172'),('17149957397072600634293','小李',38,'男','13988889999','17149957396939191194'),('17149957677831116455914','小张',25,'男','13677778888','17149957677803825334218'),('17149958265321457181560','小王',42,'男','13799990000','17149958265282171675562'),('1714995899963514840695','小陈',33,'男','13966665555','17149958999614100621095'),('17149959276111556265538','小刘',28,'女','13822221111','17149959275971865832384'),('17149982498001836260120','小周',32,'女','13833334444','1714998249788321310561');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employee` (
  `id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工编号''',
  `name` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工姓名''',
  `age` int NOT NULL COMMENT '''员工年龄''',
  `gender` enum('男','女') CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工性别''',
  `phone` varchar(15) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工电话''',
  `email` varchar(50) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''员工邮箱''',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES ('1714974123172173345502','张三',28,'男','13812345678','zhangsan@example.com'),('17149741681092521189659','李四',36,'男','13998765432','lisi@example.com'),('17149742095481024838461','王小花',22,'女','13611112222','wangxiaohua@example.com'),('17149743247571910234800','赵六',40,'男','13544443333','zhaoliu@example.com'),('17149746562851103169968','刘小红',25,'女','13755556666','liuxiaohong@example.com'),('17149815797243132198325','陈七',30,'男','13866667777','chenqi@example.com'),('1714982624349520807794','周小明',23,'男','13988889999','zhouxiaoming@example.com'),('17149826590672879562946','杨小丽',27,'女','13677778888','yangxiaoli@example.com'),('17149831610353676096239','吴八',33,'男','13799990000','wuba@example.com'),('1714983250926899865052','朱小娟',29,'女','13966665555','zhuxiaojuan@example.com'),('17149836666324052788171','韩九',31,'男','13822221111','hanjiu@example.com'),('17149837188451120575386','尤小明',26,'男','13533332222','youxiaoming@example.com'),('17149837912752705328407','刘九妹',32,'女','13833334444','liujiumei@example.com'),('17149981322701211190081','郑小兰',27,'女','13666665555','zhengxiaolan@example.com'),('admin0000','管理员',25,'男','15957101047','2239646965@qq.com');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `finance`
--

DROP TABLE IF EXISTS `finance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `finance` (
  `id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  `deposit` decimal(18,2) DEFAULT NULL COMMENT '''定金''',
  `cost` decimal(18,2) DEFAULT NULL COMMENT '''成本''',
  `amount` decimal(18,2) DEFAULT NULL COMMENT '''总金额''',
  `proj_id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `finance_project_id_fk` (`proj_id`),
  CONSTRAINT `finance_project_id_fk` FOREIGN KEY (`proj_id`) REFERENCES `project` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `finance`
--

LOCK TABLES `finance` WRITE;
/*!40000 ALTER TABLE `finance` DISABLE KEYS */;
INSERT INTO `finance` VALUES ('17149954671541617055717',0.00,0.00,0.00,'1714995467136650466941'),('17149955357911320517663',0.00,0.00,0.00,'17149955357763586832654'),('17149955841933158064369',0.00,0.00,0.00,'17149955841884013675413'),('1714995623411174176160',500.00,100.00,2000.00,'17149956234051635358594'),('1714995650824308444545',0.00,0.00,0.00,'17149956508091717477684'),('1714995712060285264852',0.00,0.00,0.00,'17149957120552262177172'),('1714995739709175684825',0.00,0.00,0.00,'17149957396939191194'),('1714995767784405808190',0.00,0.00,0.00,'17149957677803825334218'),('1714995826534696501482',0.00,0.00,0.00,'17149958265282171675562'),('17149958999663323278157',0.00,0.00,0.00,'17149958999614100621095'),('17149959276132356266207',0.00,0.00,0.00,'17149959275971865832384'),('17149982498023619456279',200.00,50.00,1000.00,'1714998249788321310561');
/*!40000 ALTER TABLE `finance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `project`
--

DROP TABLE IF EXISTS `project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `project` (
  `id` varchar(255) COLLATE utf8mb4_general_ci NOT NULL COMMENT '''项目编号''',
  `name` varchar(40) COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '''项目名''',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci COMMENT '''项目内容''',
  `start_time` datetime NOT NULL COMMENT '''项目开始日期''',
  `progress` enum('业务员沟通','设计总监分配','量房设计','平面布置图设计','合同设计','定金交付','深入图设计','效果图设计','预算表提交','项目总经理分配','施工','已完成','已取消') CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '''项目进度''',
  `update_time` datetime DEFAULT NULL COMMENT '''项目进度最后更新时间''',
  `salesman_id` varchar(255) COLLATE utf8mb4_general_ci DEFAULT '' COMMENT '''项目归属业务员编号''',
  `designer_id` varchar(255) COLLATE utf8mb4_general_ci DEFAULT '' COMMENT '''项目归属设计师编号''',
  `project_manager_id` varchar(255) COLLATE utf8mb4_general_ci DEFAULT '' COMMENT '''项目归属项目经理编号''',
  PRIMARY KEY (`id`),
  KEY `project_employee_id_fk` (`salesman_id`),
  KEY `project_employee_id_fk_2` (`designer_id`),
  KEY `project_employee_id_fk_3` (`project_manager_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `project`
--

LOCK TABLES `project` WRITE;
/*!40000 ALTER TABLE `project` DISABLE KEYS */;
INSERT INTO `project` VALUES ('1714995467136650466941','客厅装修','更换沙发、调整布局、更新灯具、更换地毯','2024-05-06 19:37:00','业务员沟通','2024-05-06 19:37:00','17149836666324052788171','',''),('17149955357763586832654','厨房装修','更新橱柜、更换燃气灶、改造水槽、增加储物柜','2024-05-06 19:38:00','设计总监分配','2024-05-06 19:46:00','17149836666324052788171','',''),('17149955841884013675413','卧室装修','更换床品、重新粉刷墙面、增加储物空间、安装风扇','2024-05-06 19:39:00','业务员沟通','2024-05-06 19:39:00','17149836666324052788171','',''),('17149956234051635358594','卫生间装修','更换马桶、更新浴室镜子、翻新浴室地板、安装淋浴房','2024-05-06 19:40:00','已完成','2024-05-06 20:14:00','17149836666324052788171','17149742095481024838461','17149837912752705328407'),('17149956508091717477684','书房装修','增加书柜、更新书桌、调整照明、改善电源布线','2024-05-06 19:40:00','业务员沟通','2024-05-06 19:40:00','17149836666324052788171','',''),('17149957120552262177172','餐厅装修1','更新餐桌椅、调整餐具储存、更换吊灯、增加绿植装饰','2024-05-06 19:41:00','业务员沟通','2024-05-06 19:41:00','17149741681092521189659','',''),('17149957396939191194','阳台装修','增加休闲椅、种植花草、搭建遮阳棚、更新地面材料','2024-05-06 19:42:00','设计总监分配','2024-05-06 19:46:00','17149741681092521189659','',''),('17149957677803825334218','儿童房装修','设计可爱壁画、更换儿童床、增加储物柜、布置学习角','2024-05-06 19:42:00','业务员沟通','2024-05-06 19:42:00','17149741681092521189659','',''),('17149958265282171675562','13799990000','改造为娱乐室、增加卫生间、调整通风、装修地面墙壁','2024-05-06 19:43:00','量房设计','2024-05-06 19:50:00','17149837188451120575386','1714983250926899865052',''),('17149958999614100621095','走廊装修','增加装饰画、更新灯具、调整家居摆放、改善光线','2024-05-06 19:44:00','设计总监分配','2024-05-06 19:45:00','1714974123172173345502','',''),('17149959275971865832384','楼梯装修','更换楼梯扶手、更新楼梯踏步、调整楼梯灯光、装饰楼梯间墙面','2024-05-06 19:45:00','业务员沟通','2024-05-06 19:45:00','1714974123172173345502','',''),('1714998249788321310561','天台装修','增加户外桌椅、布置户外休闲区、种植花草、增加遮阳设施','2024-05-06 20:24:00','已完成','2024-05-06 20:29:00','17149741681092521189659','17149742095481024838461','17149837912752705328407');
/*!40000 ALTER TABLE `project` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-05-06 21:36:49
