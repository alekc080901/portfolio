case class Company(
                      name: String,
                      structure: Array[String],
                      employees_num: Int,
                      salary_fund: Double
                  ) {
    override def toString: String = {
        name
    }
}

