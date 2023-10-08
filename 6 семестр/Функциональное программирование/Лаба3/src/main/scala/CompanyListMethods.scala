object CompanyListMethods {
    def insert[T <: Company](company_list: List[T], i: Int, value: T): List[T] =
        company_list.take(i) ++ List(value) ++ company_list.drop(i)

    def delete[T <: Company](company_list: List[T], i: Int): List[T] =
        company_list.take(i) ++ company_list.drop(i + 1)

    def set[T <: Company](company_list: List[T], i: Int, value: T): List[T] =
        company_list.take(i) ++ List(value) ++ company_list.drop(i + 1)

    def cum_sum_fund[T <: Company](company_list: List[T]): Double =
        company_list.foldLeft(0.0)(_ + _.salary_fund)

    def max_fund_company[T <: Company](company_list: List[T], custom_func: (T) => Double): String =
        company_list.maxBy(custom_func).name
}
